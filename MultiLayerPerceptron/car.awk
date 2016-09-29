{
if ($1 == "vhigh")
	buy = 1;
else if($1 == "high")
	buy = 2;
else if($1 == "med")
	buy = 3;
else if($1 =="low")
	buy=4;
if( $2 == "vhigh")
	maint=1;
else if ( $2 == "high")
	maint=2;
else if ( $2 == "med")
	maint=3;
else if ($2 =="low")
	maint=4;
if( $3 == "5more" )
	doors=5;
else if ($3 == "more")
	doors=5;
else 
	doors=$3;
if( $4 =="more" )
	persons=5;
else
	persons=$4;

if ( $5 =="small")
	lug=1;
else if ( $5 == "med" )
	lug =2;
else if ( $5 == "big")
	lug=3;

if ( $6 == "low")
	safety=1;
else if ($6 == "med")
	safety=2;
else if ($6 =="high")
	safety=3;
if( $7 == "unacc")
	ylabel=1;
else if ($6=="acc")
	ylabel=2;
else if ( $7 =="good")
	ylabel=3;
else if ( $7 == "vgood")
	ylabel=4;
print buy,maint,doors,persons,lug,safety,ylabel;
}	
