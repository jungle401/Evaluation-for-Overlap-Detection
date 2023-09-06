thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/human/T2T/output/chr1/whole_0001.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/human/T2T/output/chr1/whole_0001.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/overlaps/overlap_ver5/stable_ver/output/pbsim/human/T2T/chr1/res.ovl\
  --min_ovl_len 300\
  --max_ovl_len 6400\
  --ovl_len_bin_size 500
