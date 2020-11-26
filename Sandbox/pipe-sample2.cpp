#include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

#define DEF_STDIN 0
#define DEF_STDOUT 1
#define DEF_STDERR 2

int main() {
    const string strCommand = "./echo_cpp";
    const string strLOG = "TestString\nAcceptEchoBackTest.\n";
    const string szFunc = "PipeTest Main";

    // 子プロセスとの通信のためのパイプを作成する
    int fdInput[2] = {-1, -1};
    int fdOutput[2] = {-1, -1};
    if (!strLOG.empty()) {
        if (pipe(fdInput) != 0) {
            // パイプ作成失敗
            printf("[%s] Input用pipe作成に失敗しました(Command = %s)",
                   szFunc.c_str(), strCommand.c_str());
            return 1;
        }
        if (pipe(fdOutput) != 0) {
            // パイプ作成失敗
            printf("[%s] Output用pipe作成に失敗しました(Command = %s)",
                   szFunc.c_str(), strCommand.c_str());
            return 1;
        }
    }

    // 子プロセスを起動する
    int iChildID = fork();
    if (iChildID == -1) {
        printf("[%s] 'fork1'に失敗しました", szFunc.c_str());

        exit(-1);
    }

    if (iChildID == 0) {
        if (!strLOG.empty()) {
            // 標準入力をパイプの出力に差し替える
            int iRet = dup2(fdInput[0], DEF_STDIN);
            //              左辺の条件が右辺に含まれているため、左辺を削除します
            //              if (iRet == -1 || iRet != DEF_STDOUT) {
            if (iRet != DEF_STDIN) {
                printf("[%s] 標準入力のパイプ置換に失敗", szFunc.c_str());
                exit(-1);
            }

            // パイプの入力にエコーバックを詰める
            if (write(fdInput[1], strLOG.c_str(), strLOG.length()) < 0) {
                printf("[%s] パイプへのエコーバック入力に失敗", szFunc.c_str());
            }
            close(fdInput[0]);
            close(fdInput[1]);

            // 標準出力をOutput用のパイプの入力に差し替える
            iRet = dup2(fdOutput[1], DEF_STDOUT);
            if (iRet != DEF_STDOUT) {
                printf("[%s] 標準出力のパイプ置換に失敗", szFunc.c_str());
                exit(-1);
            }
            close(fdOutput[0]);
            close(fdOutput[1]);
        }

        // 子プロセス側の処理
        execlp(strCommand.c_str(), strCommand.c_str(), (char *)NULL);

        // 実行に失敗した
        printf("[%s] コマンド '%s' の実行に失敗しました", szFunc.c_str(),
               strCommand.c_str());

        exit(-1);
    }

    // パイプのディスクリプタを保存する
    if (!strLOG.empty()) {
        close(fdOutput[1]);
    }

    // 読み出し
    // スクリーンログを読み込む
    if (!strLOG.empty()) {
        int iStatus = 0;
        int iSize = 0;
        waitpid(iChildID, &iStatus, 0);
        close(fdOutput[1]);
        if (ioctl(fdOutput[0], FIONREAD, &iSize) == -1) {
            printf("[%s] pipeからの読み出しに失敗(Command = %s)",
                   szFunc.c_str(), strCommand.c_str());
            kill(iChildID, SIGKILL);
            waitpid(iChildID, &iStatus, 0);
            printf("[%s] 子プロセスを強制終了(ProcessID = %d)", szFunc.c_str(),
                   iChildID);
        }
        char *pszBuffer = new char[iSize + 1];
        if (read(fdOutput[0], pszBuffer, iSize) != iSize) {
            printf("[%s] pipeからの読み出しに失敗(Command = %s)",
                   szFunc.c_str(), strCommand.c_str());
            kill(iChildID, SIGKILL);
            waitpid(iChildID, &iStatus, 0);
            printf("[%s] 子プロセスを強制終了(ProcessID = %d)", szFunc.c_str(),
                   iChildID);
            delete[] pszBuffer;
        }
        pszBuffer[iSize] = '\0';
        printf("buffer start\n");
        printf("%s", pszBuffer);
        delete[] pszBuffer;
    }
    return 0;
}
