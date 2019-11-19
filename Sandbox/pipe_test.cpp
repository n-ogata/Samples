#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*!
 * @brief システムコール関数execveをラップして使い易くした(たぶん)
 * オリジナルとの違い
 *  - args[0]に実行パスを設定する必要が無い
 *  - args, envsの末尾にnull要素を追加する必要が無い
 *
 * @param[in] path 実行パス
 * @param[in] args コマンドライン引数郡
 * @param[in] envs 環境変数郡
 */
int execve(const string& path, const initializer_list<string>& args, const initializer_list<string>& envs) {
    const auto convert_string_charp(
        [](const string& arg) { return const_cast<char*>(arg.c_str()); });

    vector<char*> char_args{convert_string_charp(path)};
    transform(args.begin(), args.end(), back_inserter(char_args), convert_string_charp);
    char_args.push_back(nullptr);

    vector<char*> char_envs;
    transform(envs.begin(), envs.end(), back_inserter(char_envs), convert_string_charp);
    char_envs.push_back(nullptr);

    return ::execve(path.c_str(), char_args.data(), char_args.data());
}

bool fork_execve_stdio(const string& path, const initializer_list<string>& args,
                       const initializer_list<string>& envs,
                       const string& stdin_str, string& stdout_str,
                       int& exit_status) {
    enum
    {
        R,  // Read
        W,  // Write
        PipeCount,
    };

    const auto pipe_deleter = [](int* pipe_pointer) { ::close(*pipe_pointer); };
    using PipeCloser        = unique_ptr<int, decltype(pipe_deleter)>;

    array<int, PipeCount> pipe_p2c{};  // 親から子への通信用パイプ
    array<int, PipeCount> pipe_c2p{};  // 子から親への通信用パイプ
    if (::pipe(pipe_p2c.data()) != 0) {
        cerr << "can't create pipe(in)" << endl;
        return false;
    }
    array<PipeCloser, PipeCount> pc_p2c{
        PipeCloser(&pipe_p2c[R], pipe_deleter),
        PipeCloser(&pipe_p2c[W], pipe_deleter),
    };

    if (::pipe(pipe_c2p.data()) != 0) {
        cerr << "can't create pipe(out)" << endl;
        return false;
    }
    array<PipeCloser, PipeCount> pc_c2p{
        PipeCloser(&pipe_c2p[R], pipe_deleter),
        PipeCloser(&pipe_c2p[W], pipe_deleter),
    };

    const int ret_fork = ::fork();
    if (ret_fork < 0) {
        cerr << "can't fork" << endl;
        return false;
    }
    if (ret_fork == 0) {
        // 子プロセス側

        // 標準入力をパイプの出力に差し替える
        if (::dup2(pipe_p2c[R], STDIN_FILENO) != STDIN_FILENO) {
            cerr << "can't replace pipe(in)" << endl;
            _exit(-1);
        }

        if (!stdin_str.empty()) {
            // パイプの入力にエコーバックを詰める
            const string stdin_line(stdin_str + '\n');  // 改行無いと終端が判別できない
            if (::write(pipe_p2c[W], stdin_line.c_str(), stdin_line.length()) < 0) {
                cerr << "can't echo back pipe." << endl;
                _exit(-1);
            }
        }

        // 標準出力をOutput用のパイプの入力に差し替える
        if (::dup2(pipe_c2p[W], STDOUT_FILENO) != STDOUT_FILENO) {
            cerr << "can't replace pipe(out)" << endl;
            _exit(-1);
        }

        for (auto& closer : pc_p2c) closer.reset();
        for (auto& closer : pc_c2p) closer.reset();

        // 実行
        exit_status = execve(path, args, envs);
        _exit(exit_status);
        return false;
    }

    pc_p2c[R].reset();
    pc_c2p[W].reset();
    pc_p2c[W].release();
    pc_c2p[R].release();

    int         status      = 0;
    const pid_t ret_waitpid = ::waitpid(ret_fork, &status, 0);
    if (ret_waitpid < 0) {
        return false;
    }
    if (!WIFEXITED(status)) {
        return false;
    }

    exit_status = WEXITSTATUS(status);

    stdout_str.clear();
    array<char, 0xff> buffer;
    while (true) {
        const int ret_read = ::read(pipe_c2p[R], buffer.data(), buffer.size());
        if (ret_read == 0) break;  // EOD
        if (ret_read < 0) {
            cerr << "can't read pipe(out)" << endl;
            return false;
        }
        stdout_str += string(buffer.data(), ret_read);
    }

    return true;
}

int main() {
    string stdout_str;
    int exit_status = 0;
    if (fork_execve_stdio("./echo_cpp", {}, {}, "Hoge", stdout_str, exit_status)) {
        cout << stdout_str << exit_status << endl;
    }
    if (fork_execve_stdio("./helloworld_cpp", {}, {}, "", stdout_str, exit_status)) {
        cout << stdout_str << exit_status << endl;
    }
    if (fork_execve_stdio("/bin/ls", {}, {}, "", stdout_str, exit_status)) {
        cout << stdout_str << exit_status << endl;
    }
    if (fork_execve_stdio("./not_exe", {}, {}, "", stdout_str, exit_status)) {
        cout << stdout_str << exit_status << endl;
    }
}
