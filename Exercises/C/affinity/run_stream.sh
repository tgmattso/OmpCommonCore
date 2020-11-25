#!/bin/bash
#SBATCH -C haswell
#SBATCH -N 1
#SBATCH -t 30:00
#SBATCH -q debug

icc -qopenmp -o stream stream.c
icc -qopenmp -o stream_nft stream_nft.c

TIMESTAMP=`/bin/date +\%Y\%m\%d_\%H\%M`
myfile="mydata.$TIMESTAMP"
echo "myfile= " "$myfile" > $myfile

for k in `seq 1 5`;
do

echo "            " >> $myfile
echo "            " >> $myfile
echo "||======================" >> $myfile
echo "|| Iteration  $k        "  >> $myfile
echo "||======================" >> $myfile
echo "                " >> $myfile

echo "======================" >> $myfile
echo "Run Set 1" >> $myfile
echo "Running STREAM with first touch and OMP_PROC_BIND=close" >> $myfile
echo "export OMP_PROC_BIND=close" >> $myfile
echo "export OMP_PLACES=threads" >> $myfile
echo "======================" >> $myfile
echo "threads   Triad " >> $myfile
export OMP_PROC_BIND=close
export OMP_PLACES=threads

for i in `seq 1 64`;
do
   export OMP_NUM_THREADS=$i
   echo -n $OMP_NUM_THREADS "    " >> $myfile
   ./stream |grep Triad |awk '{print $2}' >> $myfile
done

echo "                    " >> $myfile
echo "======================" >> $myfile
echo "Run Set 2" >> $myfile
echo "Running STREAM without first touch and OMP_PROC_BIND=close" >> $myfile
echo "export OMP_PROC_BIND=close" >> $myfile
echo "export OMP_PLACES=threads" >> $myfile
echo "======================" >> $myfile
echo "threads   Triad" >> $myfile
export OMP_PROC_BIND=close
export OMP_PLACES=threads

for i in `seq 1 64`;
do
   export OMP_NUM_THREADS=$i
   echo -n $OMP_NUM_THREADS "    " >> $myfile
   ./stream_nft |grep Triad |awk '{print $2}' >> $myfile
done

echo "                    " >> $myfile
echo "======================" >> $myfile
echo "Run Set 3" >> myfile
echo "Running STREAM with first touch and OMP_PROC_BIND=spread" >> $myfile
echo "export OMP_PROC_BIND=spread" >> $myfile
echo "export OMP_PLACES=threads" >> $myfile
echo "======================" >> $myfile
echo "threads   Triad " >> $myfile
export OMP_PROC_BIND=spread
export OMP_PLACES=threads

for i in `seq 1 64`;
do
   export OMP_NUM_THREADS=$i
   echo -n $OMP_NUM_THREADS "    " >> $myfile
   ./stream |grep Triad |awk '{print $2}' >> $myfile
done

done
