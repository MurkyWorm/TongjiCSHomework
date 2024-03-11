import random


def partition(a, p, r):  # 以一个确定的基准元素a[p]对子数组a[p:r]进行划分
    i = p
    j = r+1
    x = a[p]
    while 1:
        while 1:
            i += 1
            if a[i] < x and i < r:
                pass
            else:
                break
        while 1:
            j -= 1
            if a[j] > x:
                pass
            else:
                break
        if i >= j:
            break
        mid = a[i]
        a[i] = a[j]
        a[j] = mid
    a[p] = a[j]
    a[j] = x
    return j


def randpartition(a, p, r):  # 随机化划分
    i = random.randrange(p, r)
    mid = a[i]
    a[i] = a[p]
    a[p] = mid
    return partition(a, p, r)


def randselect(a, p, r, k):  # 选择
    if p == r:
        return a[p]
    i = randpartition(a, p, r)
    j = i - p + 1
    if k <= j:
        return randselect(a, p, i, k)
    else:
        return randselect(a, i + 1, r, k-j)


a = [4, 5, 1, 6, 2, 7, 3, 8]
for i in range(1, 5):
    print(randselect(a, 0, 7, i))
