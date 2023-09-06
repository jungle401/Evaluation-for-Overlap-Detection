thesis_dir=/mnt/es/ness/johnson/thesis
project_source_dir=/mnt/es/ness/johnson/thesis/evaluation/method_2
$project_source_dir/build/app\
  --reads_file /mnt/es/ness/johnson/thesis/data/Ecoli/reads/aligned_and_sampled/minimap2/DevNet-P6C4/rngAll/aln.lsmq10.fasta\
  --mapping_file /mnt/es/ness/johnson/thesis/data/Ecoli/mapping/minimap2/DevNet_Ecoli-MG1655/chrAll/aln.lsmq10.paf\
  --overlaps_file /mnt/es/ness/johnson/thesis/CmpTools/MHAP/ver_2.1.3/use/Ecoli/DevNetP6C4/ovlp.mhp\
  --min_ovl_len 300\
  --max_ovl_len 6400\
  --ovl_len_bin_size 500
