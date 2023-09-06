thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/human/T2T/output/chr22_d20/_0001.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/human/T2T/output/chr22_d20/_0001.maf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/MHAP/ver_2.1.3/era2/pbsim3/human/d20/ovlp.mhp\
  --min_ovl_len 300\
  --max_ovl_len 6000\
  --ovl_len_bin_size 500
