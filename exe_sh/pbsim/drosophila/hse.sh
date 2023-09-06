thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/Drosophila/merged/merged.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/Drosophila/merged/merged.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/HISEA/output/pbsim3/drosophila/ovlp.hse\
  --min_ovl_len 300\
  --max_ovl_len 6400\
  --ovl_len_bin_size 500
