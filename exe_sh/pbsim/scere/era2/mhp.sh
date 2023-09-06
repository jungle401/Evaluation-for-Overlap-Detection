thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/scere/era2/output/merged/merged.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/scere/era2/output/merged/merged.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/MHAP/ver_2.1.3/era2/pbsim3/scere/ovlp.mhp\
  --min_ovl_len 300\
  --max_ovl_len 6400\
  --ovl_len_bin_size 500
