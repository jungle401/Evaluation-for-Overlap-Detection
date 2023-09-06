thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/preprocesses/fastq2fasta/output/ecoli/_0001.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/ecoli/output/_0001.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/smoothq/use/ecoli.m4\
  --min_ovl_len 300\
  --max_ovl_len 6000\
  --ovl_len_bin_size 500
