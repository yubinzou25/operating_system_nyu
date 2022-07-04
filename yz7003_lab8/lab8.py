import random
import sys
import matplotlib.pyplot as plt
from collections import deque


class FIFO:
    def __init__(self, f):
        # build a fixed-length FIFO
        self.fifo = deque(f*[-1], f)

    def query(self, page_id):
        for i in range(len(self.fifo)):
            if self.fifo[i] == page_id:
                return True
        # if didn't hit pop the end out and insert at head.
        self.fifo.append(page_id)
        return False

    def count_miss(self, trace_seq):
        miss_num = 0
        for page_id in trace_seq:
            if not self.query(page_id):
                miss_num += 1
        return miss_num


# generate a random page trace of length n, where the page numbers have values ranging from 0 to 𝑘 − 1.

def run_fifo(trace_seq, k):
    result = []
    for f in range(4, k):
        fifo_cache = FIFO(f)
        miss_count = fifo_cache.count_miss(trace_seq)
        result.append((f, miss_count))
    return result


def gen_trace_seq(n, k):
    random.seed()
    trace_seq = [random.randint(0, k - 1) for i in range(n)]
    return trace_seq


def main():
    # accepts two parameters n, k.
    n = int(sys.argv[1]) 
    k = int(sys.argv[2])
    if n < 16 or k < 8:
        exit(-1)
    trace_seq = gen_trace_seq(n, k)
    result = run_fifo(trace_seq, k)
    # show result graph
    plt.plot([x[0] for x in result], [x[1] for x in result])
    plt.xlabel('Number of Frame')
    plt.ylabel('Number of Page Fault')
    plt.show()


if __name__ == "__main__":
    main()
