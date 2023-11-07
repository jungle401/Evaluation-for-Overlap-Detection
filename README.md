# Overlap Evaluation

Evaluation for TGS reads overlap detection.

## Get started

```
git clone ssh://git@gitlab.centrilliontech.com.tw:10022/johnson/overlap_evaluation.git
cd overlap_evaluation
mkdir build && cd build
cmake ..
make app -j
```

configure execution script:

example:
```
#!/bin/bash
project_source_dir=/path/to/overlap_evaluation
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/preprocesses/fastq2fasta/output/ecoli/_0001.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/ecoli/output/_0001.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/overlaps/overlap_ver5/stable_ver/output/pbsim/ecoli/_0001/res.ovl\
  --min_ovl_len 300\
  --max_ovl_len 6000\
  --ovl_len_bin_size 500
```

example output:

```
ovlen, #pos, true_pos, #false_pos
300, 177739,168673,7092
800, 168485,166411,6650
1300, 159131,158263,4303
1800, 149783,149084,3466
2300, 134227,133613,2544
2800, 117109,116552,1650
3300, 103576,103069,1112
3800, 91870,91400,670
4300, 81656,81224,179
4800, 72953,72570,74
5300, 65149,64813,1
5800, 58280,57980,0

ovlen, sens, prec, f1sc
300, 0.949, 0.9597, 0.9543
800, 0.9877, 0.9616, 0.9745
1300, 0.9945, 0.9735, 0.9839
1800, 0.9953, 0.9773, 0.9862
2300, 0.9954, 0.9813, 0.9883
2800, 0.9952, 0.986, 0.9906
3300, 0.9951, 0.9893, 0.9922
3800, 0.9949, 0.9927, 0.9938
4300, 0.9947, 0.9978, 0.9963
4800, 0.9948, 0.999, 0.9969
5300, 0.9948, 1, 0.9974
5800, 0.9949, 1, 0.9974
```

And the result could be further visualized as figures in Results of ![the paper](https://drive.google.com/file/d/1W2BfU8hhQ_vPABtiED_d9jeyAClUYTBT/view?usp=sharing)
