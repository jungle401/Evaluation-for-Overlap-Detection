thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/data/Scerevisiae/reads/processed/chrAll/aln.lsmq10.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/data/Scerevisiae/mapping/minimap2/SRX533604_ScereS288C/chrAll/aln.lsmq10.paf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/MHAP/ver_2.1.3/use/Scere/ovlp.mhp\
  --min_ovl_len 300\
  --max_ovl_len 6400\
  --ovl_len_bin_size 500
