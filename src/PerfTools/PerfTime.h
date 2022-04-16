#ifndef _CPP_PERFTIME_H_
#define _CPP_PERFTIME_H_

namespace PerfTime {
    // 耗时统计类型
    enum class PerfType {
        PERF_E2E = 0, // 端到端类型，支持多线程
        PERF_ACC      // 累加类型，支持多线程
    };

    void StartHit(PerfType type, const char *mark); // 开始打点
    void EndHit(PerfType type, const char *mark); // 结束打点
    void OutputReport(const char *file, bool isOutputCmd = true); // 输出报告
}

#endif // _CPP_PERFTIME_H_
