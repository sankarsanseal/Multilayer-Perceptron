//
//  main.cpp
//  MultiLayerPerceptron
//
//  Created by Sankarsan Seal on 27/09/16.
//  Copyright © 2016 Sankarsan Seal. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


using namespace std;

char PATH[1024]="/Users/sankarsanseal/Documents/MultiLayerPerceptron/MultiLayerPerceptron/";


double sigmoid(double v)
{
    double result=-1;
    
    result=(1/(1+exp(-v)));
    
    //cout<<"exp(-v) : "<<exp(-v)<<" "<<v<<endl;
    
    
    return result;
    
}


void car()
{
    double input[1728][6];
    double doutput[1728][4];
    double buy;
    double maint;
    double doors;
    double persons;
    double lug;
    double safety;
    int ylabel;
    char temp[1024];
    strcpy(temp,PATH);
    srand(time(NULL));
    int noofInteration=2000;
    double eta=0.3;
    
    FILE * fp;
    fp=fopen(strcat(temp,"car.data.num.txt"),"r");
    
    if(fp!=NULL)
    {
        int noOfLayers=0;
        double ***weightmat;
        double ***weightchange;
        double **activation;
        double **delta;
        double **error;
        double induced_local=0;
        int confusionmat[4][4];
        
        
        
        int i,j,k,l,m,n;
        cout<<"Enter the no of layers:";
        cin>>noOfLayers;
        
        int noofNodes[noOfLayers];
        
        weightmat=(double ***)malloc(sizeof(double **)*noOfLayers);
        weightchange=(double ***)malloc(sizeof(double **)*noOfLayers);
        activation=(double **)malloc(sizeof(double*)*noOfLayers);
        delta=(double **)malloc(sizeof(double*)*noOfLayers);
        error=(double **)malloc(sizeof(double*)*noOfLayers);
        
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                confusionmat[i][j]=0;
        
        
        for(i=0;i<noOfLayers;i++)
        {
            if(i==0)
                noofNodes[i]=6;
            else if(i==(noOfLayers-1))
                noofNodes[i]=4;
            else
            {
                cout<<"Enter the no of nodes in layer "<<i<<":";
                cin>>noofNodes[i];
            }
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            weightmat[i]=(double **)malloc(sizeof(double*)*noofNodes[i]);
            weightchange[i]=(double **)malloc(sizeof(double*)*noofNodes[i]);
            activation[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            delta[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            error[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            for(j=0;j<noofNodes[i];j++)
            {
                activation[i][j]=0;
                delta[i][j]=0;
                error[i][j]=0;
            }
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            for(j=0;j<noofNodes[i];j++)
            {
                weightmat[i][j]=(double *)malloc(sizeof(double)*noofNodes[i+1]);
                weightchange[i][j]=(double *)malloc(sizeof(double)*noofNodes[i+1]);
                for(k=0;k<noofNodes[i+1];k++)
                {
                    weightmat[i][j][k]=((double)(rand()%10)/10);
                    weightchange[i][j][k]=0;
                }
            }
        }
        
        for(i=0;i<1728;i++)
        {
            fscanf(fp,"%lf %lf %lf %lf %lf %lf %d",&buy,&maint,&doors, &persons,
                   &lug,&safety, &ylabel);
            input[i][0]=buy;
            input[i][1]=maint;
            input[i][2]=doors;
            input[i][3]=persons;
            input[i][4]=lug;
            input[i][5]=safety;
            
            for(j=0;j<4;j++)
            {
                if(j==ylabel-1)
                    doutput[i][j]=1;
                else
                    doutput[i][j]=0;
            }
        }
        
        
        for(l=0;l<noofInteration;l++)
        {
            for(i=0;i<1728;i++)
            {
                for(m=0;m<6;m++)
                {
                    activation[0][m]=input[i][m];
                }
                
                
                
                
                for(j=1;j<noOfLayers;j++)
                {
                    
                    
                    for(k=0;k<noofNodes[j];k++)
                    {
                        error[j][k]=0;
                        delta[j][k]=0;
                        induced_local=0;
                        for(n=0;n<noofNodes[j-1];n++)
                        {
                            induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                        }
                        
                        activation[j][k]=sigmoid(induced_local);
                        
                    }
                }
                
                for(j=noOfLayers-1;j>0;j--)
                {
                    if(j==noOfLayers-1)
                    {
                        // double totalerror=0;
                        
                        for(k=0;k<noofNodes[j];k++)
                        {
                            error[j][k]=doutput[i][k]-activation[j][k];
                            delta[j][k]=error[j][k]*activation[j][k]*(1-activation[j][k]);
                            //cout<<" d:"<<doutput[i][k]<<" p:"<<activation[j][k]<<" ";
                            //totalerror+=error[j][k];
                        }
                        //cout<<endl<<"Total Error:"<<totalerror<<endl;
                    }
                    else
                    {
                        for(k=0;k<noofNodes[j];k++)
                        {
                            
                            for(n=0;n<noofNodes[j+1];n++)
                            {
                                error[j][k]+=delta[j+1][n]*weightmat[j][k][n];
                            }
                            delta[j][k]=error[j][k]*activation[j][k]*(1-activation[j][k]);
                        }
                        
                    }
                    
                    
                }
                
                for(j=0;j<noOfLayers-1;j++)
                {
                    for(k=0;k<noofNodes[j];k++)
                    {
                        for(n=0;n<noofNodes[j+1];n++)
                        {
                            weightchange[j][k][n]=eta*delta[j+1][n]*activation[j][k];
                            weightmat[j][k][n]+=weightchange[j][k][n];
                        }
                        
                    }
                }
                
                
                
                
            }
        }
        
        for(i=0;i<1728;i++)
        {
            for(m=0;m<6;m++)
            {
                activation[0][m]=input[i][m];
            }
            
            
            for(j=1;j<noOfLayers;j++)
            {
                
                for(k=0;k<noofNodes[j];k++)
                {
                    induced_local=0;
                    for(n=0;n<noofNodes[j-1];n++)
                    {
                        induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                    }
                    
                    activation[j][k]=sigmoid(induced_local);
                    
                }
            }
            
            double max=-1;
            int indexp=-1;
            int indexd=-1;
            for(m=0;m<4;m++)
            {
                if(max<activation[noOfLayers-1][m])
                {
                    max=activation[noOfLayers-1][m];
                    indexp=m;
                }
                
                if(doutput[i][m]==1)
                {
                    indexd=m;
                }
            }
            confusionmat[indexd][indexp]++;
            
        }
        
        cout<<"Confusion Matrix with Training Data"<<endl;
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                cout<<confusionmat[i][j]<<" ";
            }
            cout<<endl;
            
        }
        
        
        
        
        
        
        
        fclose(fp);
        
        strcpy(temp,PATH);
        
        fp=fopen(strcat(temp,"car.test.txt"),"r");
        
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                confusionmat[i][j]=0;
        
        for(i=0;i<170;i++)
        {
            fscanf(fp,"%lf %lf %lf %lf %lf %lf %d",&buy,&maint,&doors, &persons,
                   &lug,&safety, &ylabel);
            input[i][0]=buy;
            input[i][1]=maint;
            input[i][2]=doors;
            input[i][3]=persons;
            input[i][4]=lug;
            input[i][5]=safety;

            for(j=0;j<4;j++)
            {
                if(j==ylabel-1)
                    doutput[i][j]=1;
                else
                    doutput[i][j]=0;
            }
            
            for(m=0;m<6;m++)
            {
                activation[0][m]=input[i][m];
            }
            
            
            
            
            for(j=1;j<noOfLayers;j++)
            {
                
                
                for(k=0;k<noofNodes[j];k++)
                {
                    error[j][k]=0;
                    delta[j][k]=0;
                    induced_local=0;
                    for(n=0;n<noofNodes[j-1];n++)
                    {
                        induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                    }
                    
                    activation[j][k]=sigmoid(induced_local);
                    
                }
            }
            
            double max=-1;
            int indexp=-1;
            int indexd=-1;
            for(m=0;m<4;m++)
            {
                if(max<activation[noOfLayers-1][m])
                {
                    max=activation[noOfLayers-1][m];
                    indexp=m;
                }
                
                if(doutput[i][m]==1)
                {
                    indexd=m;
                }
            }
            confusionmat[indexd][indexp]++;
            
        }
        
        cout<<"Confusion Matrix with Testing Data"<<endl;
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
            {
                cout<<confusionmat[i][j]<<" ";
            }
            cout<<endl;
            
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            if(i!=(noOfLayers-1))
            {
                for(j=0;j<noofNodes[i];j++)
                {
                    
                    if(weightmat[i][j])
                        free(weightmat[i][j]);
                    
                    if(weightchange[i][j])
                        free(weightchange[i][j]);
                    
                    
                }
            }
            if(weightmat[i])
                free(weightmat[i]);
            if(weightchange[i])
                free(weightchange[i]);
            if(activation[i])
                free(activation[i]);
            if(delta[i])
                free(delta[i]);
            if(error[i])
                free(error[i]);
            
        }
        
        free(weightmat);
        free(weightchange);
        free(activation);
        free(delta);
        free(error);
        fclose(fp);
        
        
        
        
    }
    else
    {
        cout<<"Error with file opening"<<endl;
    }

}

void wine()
{
    double input[178][13];
    double doutput[178][3];
    
    double alcohol;
    double malic;
    double ash;
    double alcalinity;
    double magnesium;
    double phenol;
    double flavanoids;
    double nonflavanoids;
    double proanthocyanins;
    double color;
    double hue;
    double diluted;
    double proline;

    int ylabel;
    char temp[1024];
    strcpy(temp,PATH);
    srand(time(NULL));
    int noofInteration=2000;
    double eta=0.3;
    
    FILE * fp;
    fp=fopen(strcat(temp,"wine.data.num.txt"),"r");
    
    if(fp!=NULL)
    {
        int noOfLayers=0;
        double ***weightmat;
        double ***weightchange;
        double **activation;
        double **delta;
        double **error;
        double induced_local=0;
        int confusionmat[3][3];
        
        
        
        int i,j,k,l,m,n;
        cout<<"Enter the no of layers:";
        cin>>noOfLayers;
        
        int noofNodes[noOfLayers];
        
        weightmat=(double ***)malloc(sizeof(double **)*noOfLayers);
        weightchange=(double ***)malloc(sizeof(double **)*noOfLayers);
        activation=(double **)malloc(sizeof(double*)*noOfLayers);
        delta=(double **)malloc(sizeof(double*)*noOfLayers);
        error=(double **)malloc(sizeof(double*)*noOfLayers);
        
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        
        
        for(i=0;i<noOfLayers;i++)
        {
            if(i==0)
                noofNodes[i]=13;
            else if(i==(noOfLayers-1))
                noofNodes[i]=3;
            else
            {
                cout<<"Enter the no of nodes in layer "<<i<<":";
                cin>>noofNodes[i];
            }
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            weightmat[i]=(double **)malloc(sizeof(double*)*noofNodes[i]);
            weightchange[i]=(double **)malloc(sizeof(double*)*noofNodes[i]);
            activation[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            delta[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            error[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            for(j=0;j<noofNodes[i];j++)
            {
                activation[i][j]=0;
                delta[i][j]=0;
                error[i][j]=0;
            }
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            for(j=0;j<noofNodes[i];j++)
            {
                weightmat[i][j]=(double *)malloc(sizeof(double)*noofNodes[i+1]);
                weightchange[i][j]=(double *)malloc(sizeof(double)*noofNodes[i+1]);
                for(k=0;k<noofNodes[i+1];k++)
                {
                    weightmat[i][j][k]=((double)(rand()%10)/10);
                    weightchange[i][j][k]=0;
                }
            }
        }
        
        for(i=0;i<178;i++)
        {
            fscanf(fp,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&ylabel,&alcohol,&malic,
                   &ash,&alcalinity,&magnesium,
                   &phenol,&flavanoids,&nonflavanoids, &proanthocyanins, &color,
                   &hue,&diluted, &proline);
            input[i][0]=alcohol;
            input[i][1]=malic;
            input[i][2]=ash;
            input[i][3]=alcalinity;
            input[i][4]=magnesium;
            input[i][5]=phenol;
            input[i][6]=flavanoids;
            input[i][7]=nonflavanoids;
            input[i][8]=proanthocyanins;
            input[i][9]=color;
            input[i][10]=hue;
            input[i][11]=diluted;
            input[i][12]=proline;
            
            for(j=0;j<3;j++)
            {
                if(j==ylabel-1)
                    doutput[i][j]=1;
                else
                    doutput[i][j]=0;
            }
        }
        
        
        for(l=0;l<noofInteration;l++)
        {
            for(i=0;i<178;i++)
            {
                for(m=0;m<13;m++)
                {
                    activation[0][m]=input[i][m];
                }
                
                
                
                
                for(j=1;j<noOfLayers;j++)
                {
                    
                    
                    for(k=0;k<noofNodes[j];k++)
                    {
                        error[j][k]=0;
                        delta[j][k]=0;
                        induced_local=0;
                        for(n=0;n<noofNodes[j-1];n++)
                        {
                            induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                        }
                        
                        activation[j][k]=sigmoid(induced_local);
                        
                    }
                }
                
                for(j=noOfLayers-1;j>0;j--)
                {
                    if(j==noOfLayers-1)
                    {
                        // double totalerror=0;
                        
                        for(k=0;k<noofNodes[j];k++)
                        {
                            error[j][k]=doutput[i][k]-activation[j][k];
                            delta[j][k]=error[j][k]*activation[j][k]*(1-activation[j][k]);
                            //cout<<" d:"<<doutput[i][k]<<" p:"<<activation[j][k]<<" ";
                            //totalerror+=error[j][k];
                        }
                        //cout<<endl<<"Total Error:"<<totalerror<<endl;
                    }
                    else
                    {
                        for(k=0;k<noofNodes[j];k++)
                        {
                            
                            for(n=0;n<noofNodes[j+1];n++)
                            {
                                error[j][k]+=delta[j+1][n]*weightmat[j][k][n];
                            }
                            delta[j][k]=error[j][k]*activation[j][k]*(1-activation[j][k]);
                        }
                        
                    }
                    
                    
                }
                
                for(j=0;j<noOfLayers-1;j++)
                {
                    for(k=0;k<noofNodes[j];k++)
                    {
                        for(n=0;n<noofNodes[j+1];n++)
                        {
                            weightchange[j][k][n]=eta*delta[j+1][n]*activation[j][k];
                            weightmat[j][k][n]+=weightchange[j][k][n];
                        }
                        
                    }
                }
                
                
                
                
            }
        }
        
        for(i=0;i<178;i++)
        {
            for(m=0;m<13;m++)
            {
                activation[0][m]=input[i][m];
            }
            
            
            for(j=1;j<noOfLayers;j++)
            {
                
                for(k=0;k<noofNodes[j];k++)
                {
                    induced_local=0;
                    for(n=0;n<noofNodes[j-1];n++)
                    {
                        induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                    }
                    
                    activation[j][k]=sigmoid(induced_local);
                    
                }
            }
            
            double max=-1;
            int indexp=-1;
            int indexd=-1;
            for(m=0;m<3;m++)
            {
                if(max<activation[noOfLayers-1][m])
                {
                    max=activation[noOfLayers-1][m];
                    indexp=m;
                }
                
                if(doutput[i][m]==1)
                {
                    indexd=m;
                }
            }
            confusionmat[indexd][indexp]++;
            
        }
        
        cout<<"Confusion Matrix with Training Data"<<endl;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                cout<<confusionmat[i][j]<<" ";
            }
            cout<<endl;
            
        }
        
        
        
        
        
        
        
        fclose(fp);
        
        strcpy(temp,PATH);
        
        fp=fopen(strcat(temp,"wine.test.txt"),"r");
        
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        
        for(i=0;i<17;i++)
        {
            fscanf(fp,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&ylabel,&alcohol,&malic,
                   &ash,&alcalinity,&magnesium,
                   &phenol,&flavanoids,&nonflavanoids, &proanthocyanins, &color,
                   &hue,&diluted, &proline);
            input[i][0]=alcohol;
            input[i][1]=malic;
            input[i][2]=ash;
            input[i][3]=alcalinity;
            input[i][4]=magnesium;
            input[i][5]=phenol;
            input[i][6]=flavanoids;
            input[i][7]=nonflavanoids;
            input[i][8]=proanthocyanins;
            input[i][9]=color;
            input[i][10]=hue;
            input[i][11]=diluted;
            input[i][12]=proline;
            for(j=0;j<3;j++)
            {
                if(j==ylabel-1)
                    doutput[i][j]=1;
                else
                    doutput[i][j]=0;
            }
            
            for(m=0;m<13;m++)
            {
                activation[0][m]=input[i][m];
            }
            
            
            
            
            for(j=1;j<noOfLayers;j++)
            {
                
                
                for(k=0;k<noofNodes[j];k++)
                {
                    error[j][k]=0;
                    delta[j][k]=0;
                    induced_local=0;
                    for(n=0;n<noofNodes[j-1];n++)
                    {
                        induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                    }
                    
                    activation[j][k]=sigmoid(induced_local);
                    
                }
            }
            
            double max=-1;
            int indexp=-1;
            int indexd=-1;
            for(m=0;m<3;m++)
            {
                if(max<activation[noOfLayers-1][m])
                {
                    max=activation[noOfLayers-1][m];
                    indexp=m;
                }
                
                if(doutput[i][m]==1)
                {
                    indexd=m;
                }
            }
            confusionmat[indexd][indexp]++;
            
        }
        
        cout<<"Confusion Matrix with Testing Data"<<endl;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                cout<<confusionmat[i][j]<<" ";
            }
            cout<<endl;
            
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            if(i!=(noOfLayers-1))
            {
                for(j=0;j<noofNodes[i];j++)
                {
                    
                    if(weightmat[i][j])
                        free(weightmat[i][j]);
                    
                    if(weightchange[i][j])
                        free(weightchange[i][j]);
                    
                    
                }
            }
            if(weightmat[i])
                free(weightmat[i]);
            if(weightchange[i])
                free(weightchange[i]);
            if(activation[i])
                free(activation[i]);
            if(delta[i])
                free(delta[i]);
            if(error[i])
                free(error[i]);
            
        }
        
        free(weightmat);
        free(weightchange);
        free(activation);
        free(delta);
        free(error);
        fclose(fp);
        
        
        
        
    }
    else
    {
        cout<<"Error with file opening"<<endl;
    }

}


void iris()
{
    double input[150][4];
    double doutput[150][3];
    double sepal1;
    double sepal2;
    double petal1;
    double petal2;
    int ylabel;
    char temp[1024];
    strcpy(temp,PATH);
    srand(time(NULL));
    int noofInteration=2000;
    double eta=0.3;
    
    FILE * fp;
    fp=fopen(strcat(temp,"iris.data.num.txt"),"r");
    
    if(fp!=NULL)
    {
        int noOfLayers=0;
        double ***weightmat;
        double ***weightchange;
        double **activation;
        double **delta;
        double **error;
        double induced_local=0;
        int confusionmat[3][3];
    
        
        
        int i,j,k,l,m,n;
        cout<<"Enter the no of layers:";
        cin>>noOfLayers;
        
        int noofNodes[noOfLayers];
        
        weightmat=(double ***)malloc(sizeof(double **)*noOfLayers);
        weightchange=(double ***)malloc(sizeof(double **)*noOfLayers);
        activation=(double **)malloc(sizeof(double*)*noOfLayers);
        delta=(double **)malloc(sizeof(double*)*noOfLayers);
        error=(double **)malloc(sizeof(double*)*noOfLayers);
        
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        
        
        for(i=0;i<noOfLayers;i++)
        {
            if(i==0)
                noofNodes[i]=4;
            else if(i==(noOfLayers-1))
                noofNodes[i]=3;
            else
            {
                cout<<"Enter the no of nodes in layer "<<i<<":";
                cin>>noofNodes[i];
            }
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            weightmat[i]=(double **)malloc(sizeof(double*)*noofNodes[i]);
            weightchange[i]=(double **)malloc(sizeof(double*)*noofNodes[i]);
            activation[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            delta[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            error[i]=(double *)malloc(sizeof(double)*noofNodes[i]);
            for(j=0;j<noofNodes[i];j++)
            {
                activation[i][j]=0;
                delta[i][j]=0;
                error[i][j]=0;
            }
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            for(j=0;j<noofNodes[i];j++)
            {
                weightmat[i][j]=(double *)malloc(sizeof(double)*noofNodes[i+1]);
                weightchange[i][j]=(double *)malloc(sizeof(double)*noofNodes[i+1]);
                for(k=0;k<noofNodes[i+1];k++)
                {
                    weightmat[i][j][k]=((double)(rand()%10)/10);
                    weightchange[i][j][k]=0;
                }
            }
        }
        
        for(i=0;i<150;i++)
        {
            fscanf(fp,"%lf %lf %lf %lf %d",&sepal1,&sepal2,&petal1, &petal2, &ylabel);
            input[i][0]=sepal1;
            input[i][1]=sepal2;
            input[i][2]=petal1;
            input[i][3]=petal2;
            for(j=0;j<3;j++)
            {
                if(j==ylabel-1)
                    doutput[i][j]=1;
                else
                    doutput[i][j]=0;
            }
        }
        
        
        for(l=0;l<noofInteration;l++)
        {
            for(i=0;i<150;i++)
            {
                for(m=0;m<4;m++)
                {
                    activation[0][m]=input[i][m];
                }
                
                
                
                
                for(j=1;j<noOfLayers;j++)
                {
                    
                    
                    for(k=0;k<noofNodes[j];k++)
                    {
                        error[j][k]=0;
                        delta[j][k]=0;
                        induced_local=0;
                        for(n=0;n<noofNodes[j-1];n++)
                        {
                            induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                        }
                        
                        activation[j][k]=sigmoid(induced_local);
                        
                    }
                }
                
                for(j=noOfLayers-1;j>0;j--)
                {
                    if(j==noOfLayers-1)
                    {
                       // double totalerror=0;

                        for(k=0;k<noofNodes[j];k++)
                        {
                            error[j][k]=doutput[i][k]-activation[j][k];
                            delta[j][k]=error[j][k]*activation[j][k]*(1-activation[j][k]);
                            //cout<<" d:"<<doutput[i][k]<<" p:"<<activation[j][k]<<" ";
                            //totalerror+=error[j][k];
                        }
                        //cout<<endl<<"Total Error:"<<totalerror<<endl;
                    }
                    else
                    {
                        for(k=0;k<noofNodes[j];k++)
                        {

                            for(n=0;n<noofNodes[j+1];n++)
                            {
                                error[j][k]+=delta[j+1][n]*weightmat[j][k][n];
                            }
                            delta[j][k]=error[j][k]*activation[j][k]*(1-activation[j][k]);
                        }
                        
                    }
                    

                }
                
                for(j=0;j<noOfLayers-1;j++)
                {
                    for(k=0;k<noofNodes[j];k++)
                    {
                        for(n=0;n<noofNodes[j+1];n++)
                        {
                            weightchange[j][k][n]=eta*delta[j+1][n]*activation[j][k];
                            weightmat[j][k][n]+=weightchange[j][k][n];
                        }
                        
                    }
                }
                
                
                
                
            }
        }
        
        for(i=0;i<150;i++)
        {
            for(m=0;m<4;m++)
            {
                activation[0][m]=input[i][m];
            }
            
            
            for(j=1;j<noOfLayers;j++)
            {
                
                for(k=0;k<noofNodes[j];k++)
                {
                    induced_local=0;
                    for(n=0;n<noofNodes[j-1];n++)
                    {
                        induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                    }
                    
                    activation[j][k]=sigmoid(induced_local);
                    
                }
            }
            
            double max=-1;
            int indexp=-1;
            int indexd=-1;
            for(m=0;m<3;m++)
            {
                if(max<activation[noOfLayers-1][m])
                {
                    max=activation[noOfLayers-1][m];
                    indexp=m;
                }
                
                if(doutput[i][m]==1)
                {
                    indexd=m;
                }
            }
            confusionmat[indexd][indexp]++;
            
        }
        
        cout<<"Confusion Matrix with Training Data"<<endl;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                cout<<confusionmat[i][j]<<" ";
            }
            cout<<endl;
 
        }
        
        
        
        
        
        
        
        fclose(fp);
        
        strcpy(temp,PATH);
        
        fp=fopen(strcat(temp,"iris.test.txt"),"r");
        
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        
        for(i=0;i<15;i++)
        {
            fscanf(fp,"%lf %lf %lf %lf %d",&sepal1,&sepal2,&petal1, &petal2, &ylabel);
            input[i][0]=sepal1;
            input[i][1]=sepal2;
            input[i][2]=petal1;
            input[i][3]=petal2;
            for(j=0;j<3;j++)
            {
                if(j==ylabel-1)
                    doutput[i][j]=1;
                else
                    doutput[i][j]=0;
            }
            
            for(m=0;m<4;m++)
            {
                activation[0][m]=input[i][m];
            }
            
            
            
            
            for(j=1;j<noOfLayers;j++)
            {
                
                
                for(k=0;k<noofNodes[j];k++)
                {
                    error[j][k]=0;
                    delta[j][k]=0;
                    induced_local=0;
                    for(n=0;n<noofNodes[j-1];n++)
                    {
                        induced_local+=weightmat[j-1][n][k]*activation[j-1][n];
                    }
                    
                    activation[j][k]=sigmoid(induced_local);
                    
                }
            }
            
            double max=-1;
            int indexp=-1;
            int indexd=-1;
            for(m=0;m<3;m++)
            {
                if(max<activation[noOfLayers-1][m])
                {
                    max=activation[noOfLayers-1][m];
                    indexp=m;
                }
                
                if(doutput[i][m]==1)
                {
                    indexd=m;
                }
            }
                    confusionmat[indexd][indexp]++;
            
        }
        
        cout<<"Confusion Matrix with Testing Data"<<endl;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                cout<<confusionmat[i][j]<<" ";
            }
            cout<<endl;
            
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            if(i!=(noOfLayers-1))
            {
                for(j=0;j<noofNodes[i];j++)
                {
                    
                    if(weightmat[i][j])
                        free(weightmat[i][j]);
                    
                    if(weightchange[i][j])
                        free(weightchange[i][j]);
                    
                    
                }
            }
            if(weightmat[i])
                free(weightmat[i]);
            if(weightchange[i])
                free(weightchange[i]);
            if(activation[i])
                free(activation[i]);
            if(delta[i])
                free(delta[i]);
            if(error[i])
                free(error[i]);
            
        }
        
        free(weightmat);
        free(weightchange);
        free(activation);
        free(delta);
        free(error);
        fclose(fp);
        
        
        
            
    }
    else
    {
        cout<<"Error with file opening"<<endl;
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...

    int choice;
    cout<<"Enter the choice for classification problem:"<<endl;
    cout<<"1. Car Data, (Attributes 6, Classes 4)"<<endl;
    cout<<"2. Wine Data, (Atribute 13, Classes 3)"<<endl;
    cout<<"3. Iris Data, (Attribute 4, Classes 3)"<<endl;
    cout<<"Choice:";
    cin>>choice;
    switch(choice)
    {
        case 1:
            car();
            break;
        case 2:
            wine();
            break;
        case 3:
            iris();
            break;
    }
    return 0;
}
