import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = {
    "Algorithm": [
        "Merge Sort", "QuickSort", "Direct Select Sort", "HeapSort", "Radix Sort",
        "Merge Sort", "QuickSort", "Direct Select Sort", "HeapSort", "Radix Sort",
        "Merge Sort", "QuickSort", "Direct Select Sort", "HeapSort", "Radix Sort",
        "Merge Sort", "QuickSort", "Direct Select Sort", "HeapSort", "Radix Sort",
        "Merge Sort", "QuickSort", "Direct Select Sort", "HeapSort", "Radix Sort"
    ],
    "TotalTime_us": [
        2508, 0, 0, 0, 10308,
        7829, 4225, 28470, 12632, 52125,
        171445, 126415, 2744809, 308029, 610572,
        2653728, 2046890, 253548867, 3641849, 6948423,
        30796488, 24367688, 21756034745, 42528320, 88327503
    ]
}

df = pd.DataFrame(data)

dataset_sizes = [9, 99, 999, 9999, 99999]
df['DatasetSize'] = np.repeat(dataset_sizes, 5)

pivot_df = df.pivot(index="DatasetSize", columns="Algorithm", values="TotalTime_us")

plt.figure(figsize=(10, 6))
for algorithm in pivot_df.columns:
    plt.plot(pivot_df.index, pivot_df[algorithm], label=algorithm, marker='o')


plt.title("Sorting Algorithm Runtime vs Dataset Size")
plt.xlabel("Dataset Size")
plt.ylabel("Total Time (us)")
plt.yscale("log")  # Use a logarithmic scale for better visualization
plt.legend(title="Algorithm")
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.tight_layout()

plt.savefig("sorting_algorithms_runtime.png")
plt.show()

