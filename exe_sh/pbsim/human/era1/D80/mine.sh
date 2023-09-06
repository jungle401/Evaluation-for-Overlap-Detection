thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/preprocesses/fastq2fasta/output/human/T2T/depth_80/_0001.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/human/T2T/output/chr22/3M5_3M6/_0001.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/overlaps/overlap_ver5/stable_ver/output/pbsim/human/T2T/chr22/shrinked/depth_80/res.ovl\
  --min_ovl_len 300\
  --max_ovl_len 15000\
  --ovl_len_bin_size 1000
