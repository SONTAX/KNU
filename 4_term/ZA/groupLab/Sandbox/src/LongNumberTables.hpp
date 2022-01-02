#pragma once

#include <iostream>
#include <fstream>
#include <map>

#include <fort.hpp>
#include <Random/Random.hpp>

#include <GeneralAlgebra/LongArithmetic.hpp>
#include <GeneralAlgebra/LongNumber.hpp>

#include "Timer.hpp"
#include "LogDuration.hpp"

template <int First, int Last, typename Func>
inline void StaticFor(const Func& func) {
    if constexpr (First < Last) {
        func(std::integral_constant<int, First>());
        StaticFor<First + 1, Last>(func);
    }
}

inline void BaseTable(int beginLength, int endLength) {
    std::cout << "Start gen BaseTable..." << std::endl;

    fort::char_table table;

    table.set_border_style(FT_SOLID_ROUND_STYLE);

    table << fort::header << "";

    for (int i = beginLength; i < endLength; ++i)
        table << "+";

    for (int i = beginLength; i < endLength; ++i)
        table << "-";

    for (int i = beginLength; i < endLength; ++i)
        table << "*";

    for (int i = beginLength; i < endLength; ++i)
        table << "/";

    table << fort::endr;
    table << fort::header << "Base / Length";

    table[0].set_cell_text_align(fort::text_align::center);

    for (int i = 0; i < 4; ++i) {
        table[0][i * (endLength - beginLength) + 1].set_cell_span(endLength - beginLength);

        for (int j = beginLength; j < endLength; ++j)
            table << static_cast<int>(std::pow(2, j));
    }

    table << fort::endr;

    {
        LOG_DURATION("Time taken for gen BaseTable");

        StaticFor<1, 10>([&](auto i) {
            std::map<GeneralAlgebra::Operation, std::vector<int>> row;

            table << i.value;

            table[table.cur_row()].set_cell_text_align(fort::text_align::right);

            for (int j = beginLength; j < endLength; ++j) {
                auto length  = static_cast<int>(std::pow(2, j));
                auto number1 = GeneralAlgebra::LongNumber<i.value>(Ng::Random::GetString(length, 48, 57));
                auto number2 = GeneralAlgebra::LongNumber<i.value>(Ng::Random::GetString(length, 48, 57));

                row[GeneralAlgebra::Operation::Add].emplace_back(GetTime<std::milli>([&] { number1 + number2; }));
                row[GeneralAlgebra::Operation::Sub].emplace_back(GetTime<std::milli>([&] { number1 - number2; }));
                row[GeneralAlgebra::Operation::Mul].emplace_back(GetTime<std::milli>([&] { number1 * number2; }));
                row[GeneralAlgebra::Operation::Div].emplace_back(GetTime<std::milli>([&] { number1 / number2; }));
            }

            for (const auto& [operation, times] : row)
                for (const auto& time : times)
                    table << time;

            table << fort::endr;
        });
    }

    std::ofstream outfile("../../Sandbox/media/Benchmarks/BaseTable.txt");
    outfile << table.to_string();
    outfile.close();
}

inline void KaratsubaTable(int beginLength, int endLength) {
    std::cout << "Start gen KaratsubaTable..." << std::endl;

    fort::char_table table;

    table.set_border_style(FT_SOLID_ROUND_STYLE);

    table << fort::header << "";

    for (int i = beginLength; i < endLength; ++i)
        for (int j = 1; j < 10; ++j)
            table << static_cast<int>(std::pow(2, i));

    table << fort::endr;
    table << fort::header << "Limit / Base";

    for (int i = beginLength; i < endLength; ++i) {
        table[0][(i - beginLength) * 9 + 1].set_cell_span(9);

        for (int j = 1; j < 10; ++j)
            table << j;
    }

    table << fort::endr;

    {
        LOG_DURATION("Time taken for gen KaratsubaTable");

        for (int i = 2; i < 6000; i += 20) {
            table << i;

            for (int j = beginLength; j < endLength; ++j) {
                auto length = static_cast<int>(std::pow(2, j));

                table[table.cur_row()].set_cell_text_align(fort::text_align::right);

                StaticFor<1, 10>([&](auto k) {
                    auto number1 = GeneralAlgebra::LongNumber<k.value>(Ng::Random::GetString(length, 48, 57));
                    auto number2 = GeneralAlgebra::LongNumber<k.value>(Ng::Random::GetString(length, 48, 57));

                    auto naiveMulTime = GetTime<std::milli>([&] {
                        GeneralAlgebra::LongArithmetic::NaiveMul(number1, number2);
                    });

                    auto karatsubaMulTime = GetTime<std::milli>([&] {
                        GeneralAlgebra::LongArithmetic::KaratsubaMul(number1, number2, i);
                    });

                    table << std::to_string(naiveMulTime) + "/" + std::to_string(karatsubaMulTime);
                });
            }

            table << fort::endr;
        }
    }

    std::ofstream outfile("../../Sandbox/media/Benchmarks/KaratsubaTable.txt");
    outfile << table.to_string();
    outfile.close();
}

template <int CellSize>
inline void MulTable(int beginLength, int endLength) {
    using LongArithmetic = GeneralAlgebra::LongArithmetic;
    using LongNumber     = GeneralAlgebra::LongNumber<CellSize>;

    std::cout << "Start gen MulTable..." << std::endl;

    fort::char_table table;

    table.set_border_style(FT_SOLID_ROUND_STYLE);

    table << fort::header << "Length" << "NaiveMul" << "KaratsubaMul" << fort::endr;

    {
        LOG_DURATION("Time taken for gen MulTable");

        for (int i = beginLength; i < endLength; ++i) {
            auto length  = static_cast<int>(std::pow(2, i));
            auto number1 = LongNumber(Ng::Random::GetString(length, 48, 57));
            auto number2 = LongNumber(Ng::Random::GetString(length, 48, 57));

            auto naiveMulTime     = GetTime<std::milli>([&] { LongArithmetic::NaiveMul(number1, number2); });
            auto karatsubaMulTime = GetTime<std::milli>([&] { LongArithmetic::KaratsubaMul(number1, number2); });

            table[table.cur_row()].set_cell_text_align(fort::text_align::right);

            table << length << naiveMulTime << karatsubaMulTime << fort::endr;
        }
    }

    std::ofstream outfile("../../Sandbox/media/Benchmarks/MulTable.txt");
    outfile << table.to_string();
    outfile.close();
}

template <int CellSize>
inline void DivTable(int beginLength, int endLength) {
    using LongArithmetic = GeneralAlgebra::LongArithmetic;
    using LongNumber     = GeneralAlgebra::LongNumber<CellSize>;

    std::cout << "Start gen DivTable..." << std::endl;

    fort::char_table table;

    table.set_border_style(FT_SOLID_ROUND_STYLE);

    table << fort::header << "Length" << "NaiveDiv" << "LogDiv" << fort::endr;

    {
        LOG_DURATION("Time taken for gen DivTable");

        for (int i = beginLength; i < endLength; ++i) {
            auto length  = static_cast<int>(std::pow(2, i));
            auto number1 = LongNumber(Ng::Random::GetString(length, 48, 57));
            auto number2 = LongNumber(Ng::Random::GetString(length / 2, 48, 57));

            auto divNaiveTime = GetTime<std::milli>([&] { LongArithmetic::NaiveDiv(number1, number2); });
            auto divLogTime   = GetTime<std::milli>([&] { LongArithmetic::LogDiv(number1, number2);   });

            table << length << divNaiveTime << divLogTime << fort::endr;
        }
    }

    std::ofstream outfile("../../Sandbox/media/Benchmarks/DivTable.txt");
    outfile << table.to_string();
    outfile.close();
}