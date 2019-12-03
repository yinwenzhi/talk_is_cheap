from data import DataSeq

def ShellSort(ds):
    assert isinstance(ds, DataSeq), "Type Error"
    n = ds.length
    gap = n // 2
    
    while gap > 0:
        i = gap
        while i < n:
            temp = ds.data[i]
            j = i-gap
            while j >=0 and ds.data[j]>temp:
                ds.SetVal((j+gap),ds.data[j])
                j -= gap
            ds.SetVal((j+gap),temp)
            i += 1
        gap //= 2

ds=DataSeq(64)
ds.Visualize()
ds.StartTimer()
ShellSort(ds)
ds.StopTimer()
ds.SetTimeInterval(0)
ds.Visualize()
