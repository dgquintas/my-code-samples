#include <set>
#include <unordered_set>
#include <cstdlib>

#include "benchmark/benchmark_api.h"

template <typename T>
void BM_SetInsert(benchmark::State& state) {
  T data;
  while (state.KeepRunning()) {
    for (int j = 0; j < state.range_x(); ++j)
      data.insert(rand());
  }
  state.SetItemsProcessed(state.iterations() * state.range_x());
  state.SetBytesProcessed(state.iterations() * state.range_x() * sizeof(int));
  state.SetLabel("CIPOTE");
}
BENCHMARK_TEMPLATE(BM_SetInsert, std::set<int>)->Range(1 << 0, 1 << 12);
BENCHMARK_TEMPLATE(BM_SetInsert, std::unordered_set<int>)->Range(1 << 0, 1 << 12);
BENCHMARK_TEMPLATE(BM_SetInsert, std::unordered_set<int>)->Arg(512);

BENCHMARK_MAIN()
