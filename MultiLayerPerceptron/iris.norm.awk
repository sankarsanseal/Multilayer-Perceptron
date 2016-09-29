BEGIN{
max1=7.9
min1=4.3
max2=4.4
min2=2.0
max3=6.9
min3=1.0
max4=2.5
min4=0.1

}
{

if ($5 == "Iris-setosa")
	ylabel = 1;
else if($5 == "Iris-versicolor")
	ylabel = 2;
else if($5 == "Iris-virginica")
	ylabel = 3;
print ($1-min1)/(max1-min1), ($2-min2)/(max2-min2), ($3-min3)/(max3-min3) , ($4-min4)/(max4-min4), ylabel;
}
