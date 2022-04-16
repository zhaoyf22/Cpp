//
// Created by zhaoyf on 2022/4/9.
//
#include "PerfToolsTest.h"
#include "PerfTime.h"
#include <thread>
#include <chrono>

namespace PerfToolsTest{
    void fun1() {
        // 睡眠 200ms 模拟函数处理耗时
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void fun2() {
        // 睡眠 150ms 模拟函数处理耗时
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void fun3() {
        // 睡眠 100ms 模拟函数处理耗时
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void threadFun() {
        PerfTime::StartHit(PerfTime::PerfType::PERF_ACC, "fun3_cost");
        fun3();
        PerfTime::EndHit(PerfTime::PerfType::PERF_ACC, "fun3_cost");
    }

    void test()
    {
        PerfTime::StartHit(PerfTime::PerfType::PERF_E2E, "main");

        // 端到端测试
        PerfTime::StartHit(PerfTime::PerfType::PERF_E2E, "fun1_cost");
        fun1();
        PerfTime::EndHit(PerfTime::PerfType::PERF_E2E, "fun1_cost");

        // 累加耗时测试
        for (int i = 0; i < 5; ++i) {
            PerfTime::StartHit(PerfTime::PerfType::PERF_ACC, "fun2_cost");
            fun2();
            PerfTime::EndHit(PerfTime::PerfType::PERF_ACC, "fun2_cost");
        }

        // 多线程测试
        std::thread threads[10];
        for (int i = 0; i < 10; ++i) {
            threads[i] = std::thread(threadFun);
        }
        for (int i = 0; i < 10; ++i) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }

        PerfTime::EndHit(PerfTime::PerfType::PERF_E2E, "main");

        // 输出报告
        PerfTime::OutputReport("d:\\report.txt");
    }
}
