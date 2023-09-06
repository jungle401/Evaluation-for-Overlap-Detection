thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/modules/PBSIM/pbsim3_use/scere/era1/output/merged/merged.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/CmpTools/minimap2/use/as_mapper/scere/aln.paf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/minimap2/use/pbsim3/scere/era1/ovlp.paf\
  --min_ovl_len 300\
  --max_ovl_len 6400\
  --ovl_len_bin_size 500
