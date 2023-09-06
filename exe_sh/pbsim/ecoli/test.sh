project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file $project_source_dir/data/test.fasta\
  --mapping_file $project_source_dir/data/test.maf\
  --overlaps_file $project_source_dir/data/test.paf\
  --min_ovl_len 300\
  --ovl_len_bin_size 1000
