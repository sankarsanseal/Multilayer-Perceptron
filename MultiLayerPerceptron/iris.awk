BEGIN{
max1=0
min1=99
max2=0
min2=99
max3=0
min3=99
max4=0
min4=99

}
{
if(max1 < $1)
max1=$1

if(max2 < $2)
max2=$2
if(max3 < $3)
max3=$3
if(max4 < $4)
max4=$4
if(min1 > $1)
min1=$1
if(min2 > $2)
min2=$2
if(min3 > $3)
min3=$3

if(min4 > $4)
min4=$4
 print max1, min1
if ($5 == "Iris-setosa")
	ylabel = 1;
else if($5 == "Iris-versicolor")
	ylabel = 2;
else if($5 == "Iris-virginica")
	ylabel = 3;
print $1, $2, $3 , $4, ylabel;
}
END{ print max1, min1, max2, min2, max3, min3, max4, min4}
