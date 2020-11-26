#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <vector>

template <typename NumType>
struct NumWithUnit {
    NumType value;
    uint8_t unit;
};

template <typename Type>
void UnitUp(NumWithUnit<Type>& data)
{
    data.value /= 10;
    ++data.unit;
}

template <typename Type>
void UnitDown(NumWithUnit<Type>& data)
{
    data.value *= 10;
    --data.unit;
}

template <typename InType, typename OutType>
void ConvertNumWithUnit(const NumWithUnit< InType>& input,
                              NumWithUnit<OutType>& output) {
    using namespace std;
    constexpr auto OUT_MIN = numeric_limits<OutType>::min();
    constexpr auto OUT_MAX = numeric_limits<OutType>::max();
    auto in_calc(input);
    while (true) {
        if (OUT_MIN <= in_calc.value && in_calc.value <= OUT_MAX) {
            output.value = in_calc.value;
            output.unit  = in_calc.unit;
            return;
        }
        UnitUp(in_calc);
    }
}

template <typename InType, typename OutType>
void ConvertUnitEqual(const std::initializer_list<NumWithUnit< InType>>& inputs,
                            std::vector          <NumWithUnit<OutType>>& outputs) {
    using namespace std;
    outputs.resize(inputs.size());
    if (outputs.empty()) {
        return;
    }
    {
        auto ite(outputs.begin());
        for (const auto& input : inputs) {
            auto& output(*ite);
            ConvertNumWithUnit(input, output);
            ++ite;
        }
    }
    const uint8_t max_unit = [&outputs]{
        typename vector<NumWithUnit<OutType>>::iterator ite_max_unit(max_element(outputs.begin(), outputs.end(), [](const auto& a, const auto& b){return a.unit < b.unit;}));
        return ite_max_unit->unit;
    }();
    //cout << static_cast<int>(max_unit) << endl;
    while (any_of(outputs.begin(), outputs.end(), [max_unit](const auto& output){return output.unit != max_unit;})) {
        for (auto& output : outputs) {
            if (output.unit == max_unit) continue;
            UnitUp(output);
        }
    }
}

int main() {
    using namespace std;
    {
        const NumWithUnit<int32_t> input{0xffff, 0};  // 65,535
              NumWithUnit<int16_t> output{};
        ConvertNumWithUnit(input, output);
        cout << output.value << endl;
        cout << static_cast<int>(output.unit) << endl;
    }
    {
        const NumWithUnit<int32_t> input{0xffffff, 0};  // 16,777,215
              NumWithUnit<int16_t> output{};
        ConvertNumWithUnit(input, output);
        cout << output.value << endl;
        cout << static_cast<int>(output.unit) << endl;
    }
    {
        const NumWithUnit<int32_t> input1{0xffff  , 0};  // 65,535
        const NumWithUnit<int32_t> input2{0xffffff, 0};  // 16,777,215
        vector<NumWithUnit<int16_t>> outputs;
        ConvertUnitEqual({input1, input2}, outputs);
        for (const auto& output : outputs) {
            cout << output.value << endl;
            cout << static_cast<int>(output.unit) << endl;
        }
    }
}
