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
    
    
    return result;
    
}

double derivative(double v)
{
    double result;
    
    result=sigmoid(v);
    result=result*(1-result);
    return result;
}


void car()
{
    char temp[1024];
    strcpy(temp,PATH);
    FILE *fp=fopen(strcat(temp,"car.data.num.txt"),"r");
    srand(time(NULL));
    int buy;
    int maint;
    int doors;
    int persons;
    int lug;
    int safety;
    int ylabel;
    int count=0;
    int total=0;
    int noOfLayers=0;
    int noOfIteration=200;
    int i,j,k,l;
    double eta=0.5;
    int d[4];
    double induced_local=0;
    if(fp!=NULL)
    {

        
        //cout<<"Count:"<<count<<endl;
        
        
        cout<< "Enter the number of layers:";
        cin>>noOfLayers;
        
        int noOfNodes[noOfLayers];
        
        double ** neuronval;
        double ***weightmat;
        double ***weightchange;
        double **errorderive;
        neuronval=(double **)malloc(sizeof(double *)*noOfLayers);
        weightmat=(double ***)malloc(sizeof(double**)*noOfLayers);
        weightchange=(double ***)malloc(sizeof(double**)*noOfLayers);
        errorderive=(double **)malloc(sizeof(double *)*noOfLayers);
        int confusionmat[4][4];
        
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
            {
                confusionmat[i][j]=0;
            }
        
        for(i=0;i<noOfLayers;i++)
        {
            
            if(i==0)
                noOfNodes[i]=6;
            else if(i==noOfLayers-1)
                noOfNodes[i]=4;
            else
            {
                cout<<"Enter the no of Nodes in Layer "<<i<<" : ";
                cin>>noOfNodes[i];
            }
            
         //   if(i!=noOfLayers-1)
            //    noOfNodes[i]++;
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            neuronval[i]=(double *)malloc(sizeof(double)*noOfNodes[i]);
            weightmat[i]=(double **)malloc(sizeof(double *)*noOfNodes[i]);
            weightchange[i]=(double **)malloc(sizeof(double *)*noOfNodes[i]);
            errorderive[i]=(double *)malloc(sizeof(double )*noOfNodes[i]);
            
            for(j=0;j<noOfNodes[i];j++)
            {
                if(i!=noOfLayers-1)
                {
                    weightmat[i][j]=(double *)malloc(sizeof(double)*noOfNodes[i+1]);
                    weightchange[i][j]=(double *)malloc(sizeof(double)*noOfNodes[i+1]);
                    
                    for(k=0;k<noOfNodes[i+1];k++)
                    {
                        weightmat[i][j][k]=rand()%10;
                        weightchange[i][j][k]=0;
                    }
                }

                
            }

            for(j=0;j<noOfNodes[i];j++)
            {
                neuronval[i][j]=0;
                errorderive[i][j]=0;
            }
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            cout<<"Matrix "<<i<<endl;
            for(j=0;j<noOfNodes[i];j++)
            {
                
                for(k=0;k<noOfNodes[i+1];k++)
                {
                    cout<<weightmat[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"***"<<endl;
        }
        
   
        for(i=0;i<noOfIteration;i++)
        {
            fseek(fp,0,SEEK_SET);
            while(!feof(fp))
            {
                fscanf(fp,"%d %d %d %d %d %d %d", &buy, &maint, &doors, &persons, &lug, & safety, &ylabel);
                if(!feof(fp))
                {
                   // neuronval[0][0]=1;
                    neuronval[0][0]=buy;
                    neuronval[0][1]=maint;
                    neuronval[0][2]=doors;
                    neuronval[0][3]=persons;
                    neuronval[0][4]=lug;
                    neuronval[0][5]=safety;
                    
                    if(ylabel==1)
                    {
                        d[0]=1;
                        d[1]=0;
                        d[2]=0;
                        d[3]=0;
                    }
                    
                    if(ylabel==2)
                    {
                        d[0]=0;
                        d[1]=1;
                        d[2]=0;
                        d[3]=0;
                    }
                    
                    if(ylabel==3)
                    {
                        d[0]=0;
                        d[1]=0;
                        d[2]=1;
                        d[3]=0;
                    }
                    
                    if(ylabel==4)
                    {
                        d[0]=0;
                        d[1]=0;
                        d[2]=0;
                        d[3]=1;
                    }
                    
                    
                    //  cout<<buy<<":"<<ylabel<<endl;
                    //count++;
                    for(j=0;j<noOfLayers-1;j++)
                    {
                        //neuronval[j+1][0]=1;
                        for(k=0;k<noOfNodes[j+1];k++)
                        {
                            for(l=0;l<noOfNodes[j];l++)
                            {
                                induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                            }
                            neuronval[j+1][k]=sigmoid(induced_local);
                        }
                            
                        
                    }
                    
                    for(j=noOfLayers-1;j>0;j--)
                    {
                        for(k=0;k<noOfNodes[j];k++)
                        {
                            if(j==noOfLayers-1)
                            {
                                errorderive[j][k]=(d[k]-neuronval[j][k])
                                                    *(neuronval[j][k]*(1-neuronval[j][k]));
                            }
                            else
                            {
                                double sumderive=0;
                                for(l=0;l<noOfNodes[j+1];l++)
                                {
                                    sumderive+=weightmat[j][k][l]*errorderive[j+1][l];
                                }
                                errorderive[j][k]=neuronval[j][k]*(1-neuronval[j][k])*sumderive;
                                
                            }
                            
                            for(l=0;l<noOfNodes[j-1];l++)
                                {
                                    weightchange[j-1][l][k]=eta*errorderive[j][k]*neuronval[j-1][l];
                                    //cout<<"WeightChange: "<<weightchange[j-1][l][k]<<endl;
                                }
                            
                        }
                    }
                    
                    
                    
                    
                    
            /*        for(j=0;j<noOfLayers;j++)
                        
                    {
                        
                    for(k=0;k<noOfNodes[j];k++)
                        {
                            cout<<neuronval[j][k]<<" ";
                        }
                        cout<<endl<<"***"<<endl;
                    }
                    
               */
                    
                    for(j=0;j<noOfLayers-1;j++)
                        for(k=0;k<noOfNodes[j];k++)
                            for(l=0;l<noOfNodes[j+1];l++)
                            {
                                weightmat[j][k][l]+=weightchange[j][k][l];
                                //cout<<"Weight Mat: "<<weightmat[j][k][l]<<endl;
                            }
                }
                
            }
        


        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            cout<<"Matrix "<<i<<endl;
            for(j=0;j<noOfNodes[i];j++)
            {
                
                for(k=0;k<noOfNodes[i+1];k++)
                {
                    cout<<weightmat[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"*****"<<endl;
        }

        
        strcpy(temp,PATH);
        FILE * fpt=fopen(strcat(temp,"car.data.num.txt"),"r");
        
        while(!feof(fpt))
        {
            fscanf(fpt,"%d %d %d %d %d %d %d", &buy, &maint, &doors, &persons, &lug, & safety, &ylabel);
            if(!feof(fpt))
            {
                // neuronval[0][0]=1;
                neuronval[0][0]=buy;
                neuronval[0][1]=maint;
                neuronval[0][2]=doors;
                neuronval[0][3]=persons;
                neuronval[0][4]=lug;
                neuronval[0][5]=safety;
                
                if(ylabel==1)
                {
                    d[0]=1;
                    d[1]=0;
                    d[2]=0;
                    d[3]=0;
                }
                
                if(ylabel==2)
                {
                    d[0]=0;
                    d[1]=1;
                    d[2]=0;
                    d[3]=0;
                }
                
                if(ylabel==3)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=1;
                    d[3]=0;
                }
                
                if(ylabel==4)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=0;
                    d[3]=1;
                }
                
                
                //  cout<<buy<<":"<<ylabel<<endl;
                total++;
                for(j=0;j<noOfLayers-1;j++)
                {
                    //neuronval[j+1][0]=1;
                    for(k=0;k<noOfNodes[j+1];k++)
                    {
                        for(l=0;l<noOfNodes[j];l++)
                        {
                            induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                        }
                        neuronval[j+1][k]=sigmoid(induced_local);
                    }
                    
                    
                }
                double max=-1;
                int index=-1;
                for(i=0;i<4;i++)
                {
                    if(max<neuronval[noOfLayers-1][i])
                    {
                        index=i;
                        max=neuronval[noOfLayers-1][i];
                       // cout<<"max:"<<max<<"Index: "<<i;
                    }
                }
               //cout<<endl;
                
                for(i=0;i<4;i++)
                {
                    if(index==i)
                        neuronval[noOfLayers-1][i]=1;
                    else
                        neuronval[noOfLayers-1][i]=0;
                }
                
                confusionmat[ylabel-1][index]++;
                
                bool matched=true;
                
                for(i=0;i<4;i++)
                {
                    //cout<<d[i]<<" "<<neuronval[noOfLayers-1][i]<<" ";
                    if(d[i]==neuronval[noOfLayers-1][i])
                        continue;
                    else
                    {
                        matched=false;
                        break;
                    }
                    
                    
                }
                
                //cout<<endl;
                
                if(matched)
                    count++;
                
                
            }
            
            
            
                
                
        }
        cout<< "Confusion Matrix of Training Data"<<endl;
        
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
               cout<<confusionmat[i][j]<<" ";
            cout<<endl;
        }
            cout<< "Accuracy: "<<(double)count/total<<endl;
        
        fclose(fpt);
        
        total=0;
        count=0;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                confusionmat[i][j]=0;
        
        strcpy(temp,PATH);
        fpt=fopen(strcat(temp,"car.test.txt"),"r");
        
        while(!feof(fpt))
        {
            fscanf(fpt,"%d %d %d %d %d %d %d", &buy, &maint, &doors, &persons, &lug, & safety, &ylabel);
            if(!feof(fpt))
            {
                // neuronval[0][0]=1;
                neuronval[0][0]=buy;
                neuronval[0][1]=maint;
                neuronval[0][2]=doors;
                neuronval[0][3]=persons;
                neuronval[0][4]=lug;
                neuronval[0][5]=safety;
                
                if(ylabel==1)
                {
                    d[0]=1;
                    d[1]=0;
                    d[2]=0;
                    d[3]=0;
                }
                
                if(ylabel==2)
                {
                    d[0]=0;
                    d[1]=1;
                    d[2]=0;
                    d[3]=0;
                }
                
                if(ylabel==3)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=1;
                    d[3]=0;
                }
                
                if(ylabel==4)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=0;
                    d[3]=1;
                }
                
                
                //  cout<<buy<<":"<<ylabel<<endl;
                total++;
                for(j=0;j<noOfLayers-1;j++)
                {
                    //neuronval[j+1][0]=1;
                    for(k=0;k<noOfNodes[j+1];k++)
                    {
                        for(l=0;l<noOfNodes[j];l++)
                        {
                            induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                        }
                        neuronval[j+1][k]=sigmoid(induced_local);
                    }
                    
                    
                }
                double max=-1;
                int index=-1;
                for(i=0;i<4;i++)
                {
                    if(max<neuronval[noOfLayers-1][i])
                    {
                        index=i;
                        max=neuronval[noOfLayers-1][i];
                        // cout<<"max:"<<max<<"Index: "<<i;
                    }
                }
                //cout<<endl;
                
                for(i=0;i<4;i++)
                {
                    if(index==i)
                        neuronval[noOfLayers-1][i]=1;
                    else
                        neuronval[noOfLayers-1][i]=0;
                }
                
                confusionmat[ylabel-1][index]++;
                
                bool matched=true;
                
                for(i=0;i<4;i++)
                {
                    //cout<<d[i]<<" "<<neuronval[noOfLayers-1][i]<<" ";
                    if(d[i]==neuronval[noOfLayers-1][i])
                        continue;
                    else
                    {
                        matched=false;
                        break;
                    }
                    
                    
                }
                
                //cout<<endl;
                
                if(matched)
                    count++;
                
                
            }
            
            
            
            
            
        }

        cout<< "Confusion Matrix of Testing Data"<<endl;
        
        for(i=0;i<4;i++)
        {
            for(j=0;j<4;j++)
                cout<<confusionmat[i][j]<<" ";
            cout<<endl;
        }
        cout<< "Accuracy: "<<(double)count/total<<endl;
        

        
        for(i=0;i<noOfLayers;i++)
        {
            free(neuronval[i]);

            for(j=0;j<noOfNodes[i];j++)
            {
                free(weightmat[i][j]);
                free(weightchange[i][j]);
            }
            free(weightmat[i]);
            free(weightchange[i]);
            
        }
        free(neuronval);
        free(weightmat);
        free(weightchange);
        
        fclose(fpt);
        fclose(fp);
        
    }
    else
    {
        cout<<"Problem with file open."<<endl;
    }
}

void wine()
{
    char temp[1024];
    strcpy(temp,PATH);
    FILE *fp=fopen(strcat(temp,"wine.data.num.txt"),"r");
    srand(time(NULL));
    double alcohol;
    double malic;
    double ash;
    double alcalinity;
    double magnesium;
    double phenols;
    double flavanoids;
    double nonflavanoid;
    double proanthocyanins;
    double color;
    double hue;
    double diluted;
    double proline;
    int ylabel;
    int count=0;
    int total=0;
    int noOfLayers=0;
    int noOfIteration=200;
    int i,j,k,l;
    double eta=0.3;
    int d[3];
    double induced_local=0;
    if(fp!=NULL)
    {
        
        
        //cout<<"Count:"<<count<<endl;
        
        
        cout<< "Enter the number of layers:";
        cin>>noOfLayers;
        
        int noOfNodes[noOfLayers];
        
        double ** neuronval;
        double ***weightmat;
        double ***weightchange;
        double **errorderive;
        neuronval=(double **)malloc(sizeof(double *)*noOfLayers);
        weightmat=(double ***)malloc(sizeof(double**)*noOfLayers);
        weightchange=(double ***)malloc(sizeof(double**)*noOfLayers);
        errorderive=(double **)malloc(sizeof(double *)*noOfLayers);
        int confusionmat[3][3];
        
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        
        for(i=0;i<noOfLayers;i++)
        {
            
            if(i==0)
                noOfNodes[i]=13;
            else if(i==noOfLayers-1)
                noOfNodes[i]=3;
            else
            {
                cout<<"Enter the no of Nodes in Layer "<<i<<" : ";
                cin>>noOfNodes[i];
            }
            
            //   if(i!=noOfLayers-1)
            //    noOfNodes[i]++;
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            neuronval[i]=(double *)malloc(sizeof(double)*noOfNodes[i]);
            weightmat[i]=(double **)malloc(sizeof(double *)*noOfNodes[i]);
            weightchange[i]=(double **)malloc(sizeof(double *)*noOfNodes[i]);
            errorderive[i]=(double *)malloc(sizeof(double )*noOfNodes[i]);
            
            for(j=0;j<noOfNodes[i];j++)
            {
                if(i!=noOfLayers-1)
                {
                    weightmat[i][j]=(double *)malloc(sizeof(double)*noOfNodes[i+1]);
                    weightchange[i][j]=(double *)malloc(sizeof(double)*noOfNodes[i+1]);
                    
                    for(k=0;k<noOfNodes[i+1];k++)
                    {
                        weightmat[i][j][k]=rand()%10;
                        weightchange[i][j][k]=0;
                    }
                }
                
                
            }
            
            for(j=0;j<noOfNodes[i];j++)
            {
                neuronval[i][j]=0;
                errorderive[i][j]=0;
            }
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            cout<<"Matrix "<<i<<endl;
            for(j=0;j<noOfNodes[i];j++)
            {
                
                for(k=0;k<noOfNodes[i+1];k++)
                {
                    cout<<weightmat[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"***"<<endl;
        }
        
        
        for(i=0;i<noOfIteration;i++)
        {
            fseek(fp,0,SEEK_SET);
            while(!feof(fp))
            {
                fscanf(fp,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &ylabel, &alcohol, &malic, &ash, &alcalinity, &magnesium, &phenols, &flavanoids, &nonflavanoid, &proanthocyanins, &color, &hue,&diluted,&proline);
                //cout<<flavanoids<<" "<< nonflavanoid<<endl;
                if(!feof(fp))
                {
                    // neuronval[0][0]=1;
                    neuronval[0][0]=alcohol;
                    neuronval[0][1]=malic;
                    neuronval[0][2]=ash;
                    neuronval[0][3]=alcalinity;
                    neuronval[0][4]=magnesium;
                    neuronval[0][5]=phenols;
                    neuronval[0][6]=flavanoids;
                    neuronval[0][7]=nonflavanoid;
                    neuronval[0][8]=proanthocyanins;
                    neuronval[0][9]=color;
                    neuronval[0][10]=hue;
                    neuronval[0][11]=diluted;
                    neuronval[0][12]=proline;
                    
                    if(ylabel==1)
                    {
                        d[0]=1;
                        d[1]=0;
                        d[2]=0;

                    }
                    
                    if(ylabel==2)
                    {
                        d[0]=0;
                        d[1]=1;
                        d[2]=0;
                        
                    }
                    
                    if(ylabel==3)
                    {
                        d[0]=0;
                        d[1]=0;
                        d[2]=1;
                        
                    }
                    

                    
                    //  cout<<buy<<":"<<ylabel<<endl;
                    //count++;
                    for(j=0;j<noOfLayers-1;j++)
                    {
                        //neuronval[j+1][0]=1;
                        for(k=0;k<noOfNodes[j+1];k++)
                        {
                            for(l=0;l<noOfNodes[j];l++)
                            {
                                induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                            }
                            neuronval[j+1][k]=sigmoid(induced_local);
                        }
                        
                        
                    }
                    
                    for(j=noOfLayers-1;j>0;j--)
                    {
                        for(k=0;k<noOfNodes[j];k++)
                        {
                            if(j==noOfLayers-1)
                            {
                                errorderive[j][k]=(d[k]-neuronval[j][k])
                                *(neuronval[j][k]*(1-neuronval[j][k]));
                            }
                            else
                            {
                                double sumderive=0;
                                for(l=0;l<noOfNodes[j+1];l++)
                                {
                                    sumderive+=weightmat[j][k][l]*errorderive[j+1][l];
                                }
                                errorderive[j][k]=neuronval[j][k]*(1-neuronval[j][k])*sumderive;
                                
                            }
                            
                            for(l=0;l<noOfNodes[j-1];l++)
                            {
                                weightchange[j-1][l][k]=eta*errorderive[j][k]*neuronval[j-1][l];
                                //cout<<"WeightChange: "<<weightchange[j-1][l][k]<<endl;
                            }
                            
                        }
                    }
 
                    
                  
                    
                    
                    /*        for(j=0;j<noOfLayers;j++)
                     
                     {
                     
                     for(k=0;k<noOfNodes[j];k++)
                     {
                     cout<<neuronval[j][k]<<" ";
                     }
                     cout<<endl<<"***"<<endl;
                     }
                     
                     */
                    
                   for(j=0;j<noOfLayers-1;j++)
                        for(k=0;k<noOfNodes[j];k++)
                            for(l=0;l<noOfNodes[j+1];l++)
                            {
                                weightmat[j][k][l]+=weightchange[j][k][l];
                                //cout<<"Weight Mat: "<<weightmat[j][k][l]<<endl;
                            }
                }
                
            }
            
            
            
        }

  
        for(i=0;i<noOfLayers-1;i++)
        {
            cout<<"Matrix "<<i<<endl;
            for(j=0;j<noOfNodes[i];j++)
            {
                
                for(k=0;k<noOfNodes[i+1];k++)
                {
                    cout<<weightmat[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"*****"<<endl;
        }
        
        
        strcpy(temp,PATH);
        FILE * fpt=fopen(strcat(temp,"wine.data.num.txt"),"r");
        
        while(!feof(fpt))
        {
            fscanf(fpt,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ", &ylabel, &alcohol, &malic, &ash, &alcalinity, &magnesium, &phenols, &flavanoids, &nonflavanoid, &proanthocyanins, &color, &hue,&diluted,&proline);
            if(!feof(fpt))
            {
                // neuronval[0][0]=1;
                neuronval[0][0]=alcohol;
                neuronval[0][1]=malic;
                neuronval[0][2]=ash;
                neuronval[0][3]=alcalinity;
                neuronval[0][4]=magnesium;
                neuronval[0][5]=phenols;
                neuronval[0][6]=flavanoids;
                neuronval[0][7]=nonflavanoid;
                neuronval[0][8]=proanthocyanins;
                neuronval[0][9]=color;
                neuronval[0][10]=hue;
                neuronval[0][11]=diluted;
                neuronval[0][12]=proline;
                
                if(ylabel==1)
                {
                    d[0]=1;
                    d[1]=0;
                    d[2]=0;
                    
                }
                
                if(ylabel==2)
                {
                    d[0]=0;
                    d[1]=1;
                    d[2]=0;
                    
                }
                
                if(ylabel==3)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=1;
                    
                }
                
                
                
                
                //  cout<<buy<<":"<<ylabel<<endl;
                total++;
                for(j=0;j<noOfLayers-1;j++)
                {
                    //neuronval[j+1][0]=1;
                    for(k=0;k<noOfNodes[j+1];k++)
                    {
                        for(l=0;l<noOfNodes[j];l++)
                        {
                            induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                        }
                        neuronval[j+1][k]=sigmoid(induced_local);
                    }
                    
                    
                }
                double max=-1;
                int index=-1;
                for(i=0;i<3;i++)
                {
                    if(max<neuronval[noOfLayers-1][i])
                    {
                        index=i;
                        max=neuronval[noOfLayers-1][i];
                        // cout<<"max:"<<max<<"Index: "<<i;
                    }
                }
                //cout<<endl;
                
                confusionmat[ylabel-1][index]++;
                
                for(i=0;i<3;i++)
                {
                    if(index==i)
                        neuronval[noOfLayers-1][i]=1;
                    else
                        neuronval[noOfLayers-1][i]=0;
                }
                
                bool matched=true;
                
                for(i=0;i<3;i++)
                {
                    //cout<<d[i]<<" "<<neuronval[noOfLayers-1][i]<<" ";
                    if(d[i]==neuronval[noOfLayers-1][i])
                        continue;
                    else
                    {
                        matched=false;
                        break;
                    }
                    
                    
                }
                
                //cout<<endl;
                
                if(matched)
                    count++;
                
                
            }
            
            
            
            
            
        }
        
        cout<< "Confusion Matrix of Training Data"<<endl;
        
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
                cout<<confusionmat[i][j]<<" ";
            cout<<endl;
        }
        cout<< "Accuracy: "<<(double)count/total<<endl;
        
        fclose(fpt);
        total=0;
        count=0;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        strcpy(temp,PATH);
         fpt=fopen(strcat(temp,"wine.test.txt"),"r");
        
        while(!feof(fpt))
        {
          fscanf(fpt,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf ", &ylabel, &alcohol, &malic, &ash, &alcalinity, &magnesium, &phenols, &flavanoids, &nonflavanoid, &proanthocyanins, &color, &hue,&diluted,&proline);
            if(!feof(fpt))
            {
                // neuronval[0][0]=1;
                neuronval[0][0]=alcohol;
                neuronval[0][1]=malic;
                neuronval[0][2]=ash;
                neuronval[0][3]=alcalinity;
                neuronval[0][4]=magnesium;
                neuronval[0][5]=phenols;
                neuronval[0][6]=flavanoids;
                neuronval[0][7]=nonflavanoid;
                neuronval[0][8]=proanthocyanins;
                neuronval[0][9]=color;
                neuronval[0][10]=hue;
                neuronval[0][11]=diluted;
                neuronval[0][12]=proline;
                
                if(ylabel==1)
                {
                    d[0]=1;
                    d[1]=0;
                    d[2]=0;

                }
                
                if(ylabel==2)
                {
                    d[0]=0;
                    d[1]=1;
                    d[2]=0;

                }
                
                if(ylabel==3)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=1;

                }
                

                
                
                //  cout<<buy<<":"<<ylabel<<endl;
                total++;
                for(j=0;j<noOfLayers-1;j++)
                {
                    //neuronval[j+1][0]=1;
                    for(k=0;k<noOfNodes[j+1];k++)
                    {
                        for(l=0;l<noOfNodes[j];l++)
                        {
                            induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                        }
                        neuronval[j+1][k]=sigmoid(induced_local);
                    }
                    
                    
                }
                double max=-1;
                int index=-1;
                for(i=0;i<3;i++)
                {
                    if(max<neuronval[noOfLayers-1][i])
                    {
                        index=i;
                        max=neuronval[noOfLayers-1][i];
                        // cout<<"max:"<<max<<"Index: "<<i;
                    }
                }
                //cout<<endl;
                
                confusionmat[ylabel-1][index]++;
                
                for(i=0;i<3;i++)
                {
                    if(index==i)
                        neuronval[noOfLayers-1][i]=1;
                    else
                        neuronval[noOfLayers-1][i]=0;
                }
                
                bool matched=true;
                
                for(i=0;i<3;i++)
                {
                    //cout<<d[i]<<" "<<neuronval[noOfLayers-1][i]<<" ";
                    if(d[i]==neuronval[noOfLayers-1][i])
                        continue;
                    else
                    {
                        matched=false;
                        break;
                    }
                    
                    
                }
                
                //cout<<endl;
                
                if(matched)
                    count++;
                
                
            }
            
            
            
            
            
        }
        
        cout<< "Confusion Matrix of Testing Data"<<endl;
        
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
                cout<<confusionmat[i][j]<<" ";
            cout<<endl;
        }
        cout<< "Accuracy: "<<(double)count/total<<endl;
        
        
        
        
        for(i=0;i<noOfLayers;i++)
        {
            free(neuronval[i]);
            
            for(j=0;j<noOfNodes[i];j++)
            {
                free(weightmat[i][j]);
                free(weightchange[i][j]);
            }
            free(weightmat[i]);
            free(weightchange[i]);
            
        }
        free(neuronval);
        free(weightmat);
        free(weightchange);
        
        fclose(fpt);
        fclose(fp);
        
    }
    else
    {
        cout<<"Problem with file open."<<endl;
    }

}

void iris()
{
    char temp[1024];
    strcpy(temp,PATH);
    FILE *fp=fopen(strcat(temp,"iris.data.num.txt"),"r");
    srand(time(NULL));
    double sepal1;
    double sepal2;
    double petal1;
    double petal2;
    int ylabel;
    int count=0;
    int total=0;
    int noOfLayers=0;
    int noOfIteration=200;
    int i,j,k,l;
    double eta=0.1;
    int d[3];
    double induced_local=0;
    if(fp!=NULL)
    {
        
        
        //cout<<"Count:"<<count<<endl;
        
        
        cout<< "Enter the number of layers:";
        cin>>noOfLayers;
        
        int noOfNodes[noOfLayers];
        
        double ** neuronval;
        double ***weightmat;
        double ***weightchange;
        double **errorderive;
        neuronval=(double **)malloc(sizeof(double *)*noOfLayers);
        weightmat=(double ***)malloc(sizeof(double**)*noOfLayers);
        weightchange=(double ***)malloc(sizeof(double**)*noOfLayers);
        errorderive=(double **)malloc(sizeof(double *)*noOfLayers);
        int confusionmat[3][3];
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        
        for(i=0;i<noOfLayers;i++)
        {
            
            if(i==0)
                noOfNodes[i]=4;
            else if(i==noOfLayers-1)
                noOfNodes[i]=3;
            else
            {
                cout<<"Enter the no of Nodes in Layer "<<i<<" : ";
                cin>>noOfNodes[i];
            }
            
            //   if(i!=noOfLayers-1)
            //    noOfNodes[i]++;
        }
        
        for(i=0;i<noOfLayers;i++)
        {
            neuronval[i]=(double *)malloc(sizeof(double)*noOfNodes[i]);
            weightmat[i]=(double **)malloc(sizeof(double *)*noOfNodes[i]);
            weightchange[i]=(double **)malloc(sizeof(double *)*noOfNodes[i]);
            errorderive[i]=(double *)malloc(sizeof(double )*noOfNodes[i]);
            
            for(j=0;j<noOfNodes[i];j++)
            {
                if(i!=noOfLayers-1)
                {
                    weightmat[i][j]=(double *)malloc(sizeof(double)*noOfNodes[i+1]);
                    weightchange[i][j]=(double *)malloc(sizeof(double)*noOfNodes[i+1]);
                    
                    for(k=0;k<noOfNodes[i+1];k++)
                    {
                        weightmat[i][j][k]=rand()%10;
                        weightchange[i][j][k]=0;
                    }
                }
                
                
            }
            
            for(j=0;j<noOfNodes[i];j++)
            {
                neuronval[i][j]=0;
                errorderive[i][j]=0;
            }
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            cout<<"Matrix "<<i<<endl;
            for(j=0;j<noOfNodes[i];j++)
            {
                
                for(k=0;k<noOfNodes[i+1];k++)
                {
                    cout<<weightmat[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"***"<<endl;
        }
        
        
        for(i=0;i<noOfIteration;i++)
        {
            fseek(fp,0,SEEK_SET);
            while(!feof(fp))
            {
                fscanf(fp,"%lf %lf %lf %lf %d", &sepal1,&sepal2,&petal1,&petal2, &ylabel);
                if(!feof(fp))
                {
                    // neuronval[0][0]=1;
                    neuronval[0][0]=sepal1;
                    neuronval[0][1]=sepal2;
                    neuronval[0][2]=petal1;
                    neuronval[0][3]=petal2;
                    
                    if(ylabel==1)
                    {
                        d[0]=1;
                        d[1]=0;
                        d[2]=0;

                    }
                    
                    if(ylabel==2)
                    {
                        d[0]=0;
                        d[1]=1;
                        d[2]=0;

                    }
                    
                    if(ylabel==3)
                    {
                        d[0]=0;
                        d[1]=0;
                        d[2]=1;
                    }
                    

                    
                    
                    //  cout<<buy<<":"<<ylabel<<endl;
                    //count++;
                    for(j=0;j<noOfLayers-1;j++)
                    {
                        //neuronval[j+1][0]=1;
                        for(k=0;k<noOfNodes[j+1];k++)
                        {
                            for(l=0;l<noOfNodes[j];l++)
                            {
                                induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                            }
                            neuronval[j+1][k]=sigmoid(induced_local);
                        }
                        
                        
                    }
                    
                    for(j=noOfLayers-1;j>0;j--)
                    {
                        for(k=0;k<noOfNodes[j];k++)
                        {
                            if(j==noOfLayers-1)
                            {
                                errorderive[j][k]=(d[k]-neuronval[j][k])
                                *(neuronval[j][k]*(1-neuronval[j][k]));
                            }
                            else
                            {
                                double sumderive=0;
                                for(l=0;l<noOfNodes[j+1];l++)
                                {
                                    sumderive+=weightmat[j][k][l]*errorderive[j+1][l];
                                }
                                errorderive[j][k]=neuronval[j][k]*(1-neuronval[j][k])*sumderive;
                                
                            }
                            
                            for(l=0;l<noOfNodes[j-1];l++)
                            {
                                weightchange[j-1][l][k]=eta*errorderive[j][k]*neuronval[j-1][l];
                                //cout<<"WeightChange: "<<weightchange[j-1][l][k]<<endl;
                            }
                            
                        }
                    }
                    
                    
                    
                    
                    
                    /*        for(j=0;j<noOfLayers;j++)
                     
                     {
                     
                     for(k=0;k<noOfNodes[j];k++)
                     {
                     cout<<neuronval[j][k]<<" ";
                     }
                     cout<<endl<<"***"<<endl;
                     }
                     
                     */
                    
                    for(j=0;j<noOfLayers-1;j++)
                        for(k=0;k<noOfNodes[j];k++)
                            for(l=0;l<noOfNodes[j+1];l++)
                            {
                                weightmat[j][k][l]+=weightchange[j][k][l];
                                //cout<<"Weight Mat: "<<weightmat[j][k][l]<<endl;
                            }
                }
                
            }
            
            
            
        }
        
        for(i=0;i<noOfLayers-1;i++)
        {
            cout<<"Matrix "<<i<<endl;
            for(j=0;j<noOfNodes[i];j++)
            {
                
                for(k=0;k<noOfNodes[i+1];k++)
                {
                    cout<<weightmat[i][j][k]<<" ";
                }
                cout<<endl;
            }
            cout<<"*****"<<endl;
        }
        
        
        
        strcpy(temp,PATH);
        FILE * fpt=fopen(strcat(temp,"iris.data.num.txt"),"r");
        
        while(!feof(fpt))
        {
                fscanf(fpt,"%lf %lf %lf %lf %d", &sepal1,&sepal2,&petal1,&petal2, &ylabel);
            if(!feof(fpt))
            {
                // neuronval[0][0]=1;
                neuronval[0][0]=sepal1;
                neuronval[0][1]=sepal2;
                neuronval[0][2]=petal1;
                neuronval[0][3]=petal2;

                
                if(ylabel==1)
                {
                    d[0]=1;
                    d[1]=0;
                    d[2]=0;

                }
                
                if(ylabel==2)
                {
                    d[0]=0;
                    d[1]=1;
                    d[2]=0;

                }
                
                if(ylabel==3)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=1;

                }

                
                //  cout<<buy<<":"<<ylabel<<endl;
                total++;
                for(j=0;j<noOfLayers-1;j++)
                {
                    //neuronval[j+1][0]=1;
                    for(k=0;k<noOfNodes[j+1];k++)
                    {
                        for(l=0;l<noOfNodes[j];l++)
                        {
                            induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                        }
                        neuronval[j+1][k]=sigmoid(induced_local);
                    }
                    
                    
                }
                double max=-1;
                int index=-1;
                for(i=0;i<3;i++)
                {
                    if(max<neuronval[noOfLayers-1][i])
                    {
                        index=i;
                        max=neuronval[noOfLayers-1][i];
                        // cout<<"max:"<<max<<"Index: "<<i;
                    }
                }
                //cout<<endl;
                
                confusionmat[ylabel-1][index]++;
                
                for(i=0;i<3;i++)
                {
                    if(index==i)
                        neuronval[noOfLayers-1][i]=1;
                    else
                        neuronval[noOfLayers-1][i]=0;
                }
                
                bool matched=true;
                
                for(i=0;i<3;i++)
                {
                   // cout<<d[i]<<" "<<neuronval[noOfLayers-1][i]<<" ";
                    if(d[i]==neuronval[noOfLayers-1][i])
                        continue;
                    else
                    {
                        matched=false;
                        break;
                    }
                    
                    
                }
                
               // cout<<endl;
                
                if(matched)
                    count++;
                
                
            }
            
            
            
            
            
        }
        cout<< "Confusion Matrix of Training Data"<<endl;
        
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
                cout<<confusionmat[i][j]<<" ";
            cout<<endl;
        }
        cout<< "Accuracy: "<<(double)count/total<<endl;
        
        fclose(fpt);
        
        
        
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                confusionmat[i][j]=0;
        count=0;
        total=0;
        strcpy(temp,PATH);
        fpt=fopen(strcat(temp,"iris.test.txt"),"r");
        
        while(!feof(fpt))
        {
            fscanf(fpt,"%lf %lf %lf %lf %d", &sepal1,&sepal2,&petal1,&petal2, &ylabel);
            if(!feof(fpt))
            {
                // neuronval[0][0]=1;
                neuronval[0][0]=sepal1;
                neuronval[0][1]=sepal2;
                neuronval[0][2]=petal1;
                neuronval[0][3]=petal2;
                
                
                if(ylabel==1)
                {
                    d[0]=1;
                    d[1]=0;
                    d[2]=0;
                    
                }
                
                if(ylabel==2)
                {
                    d[0]=0;
                    d[1]=1;
                    d[2]=0;
                    
                }
                
                if(ylabel==3)
                {
                    d[0]=0;
                    d[1]=0;
                    d[2]=1;
                    
                }
                
                
                //  cout<<buy<<":"<<ylabel<<endl;
                total++;
                for(j=0;j<noOfLayers-1;j++)
                {
                    //neuronval[j+1][0]=1;
                    for(k=0;k<noOfNodes[j+1];k++)
                    {
                        for(l=0;l<noOfNodes[j];l++)
                        {
                            induced_local=+(weightmat[j][l][k])*neuronval[j][l];
                        }
                        neuronval[j+1][k]=sigmoid(induced_local);
                    }
                    
                    
                }
                double max=-1;
                int index=-1;
                for(i=0;i<3;i++)
                {
                    if(max<neuronval[noOfLayers-1][i])
                    {
                        index=i;
                        max=neuronval[noOfLayers-1][i];
                        // cout<<"max:"<<max<<"Index: "<<i;
                    }
                }
                //cout<<endl;
                
                confusionmat[ylabel-1][index]++;
                
                for(i=0;i<3;i++)
                {
                    if(index==i)
                        neuronval[noOfLayers-1][i]=1;
                    else
                        neuronval[noOfLayers-1][i]=0;
                }
                
                bool matched=true;
                
                for(i=0;i<3;i++)
                {
                    // cout<<d[i]<<" "<<neuronval[noOfLayers-1][i]<<" ";
                    if(d[i]==neuronval[noOfLayers-1][i])
                        continue;
                    else
                    {
                        matched=false;
                        break;
                    }
                    
                    
                }
                
                // cout<<endl;
                
                if(matched)
                    count++;
                
                
            }
            
            
            
            
            
        }
        cout<< "Confusion Matrix of Testing Data"<<endl;
        
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
                cout<<confusionmat[i][j]<<" ";
            cout<<endl;
        }
        cout<< "Accuracy: "<<(double)count/total<<endl;
        

        
        for(i=0;i<noOfLayers;i++)
        {
            free(neuronval[i]);
            
            for(j=0;j<noOfNodes[i];j++)
            {
                free(weightmat[i][j]);
                free(weightchange[i][j]);
            }
            free(weightmat[i]);
            free(weightchange[i]);
            
        }
        free(neuronval);
        free(weightmat);
        free(weightchange);
        
        fclose(fpt);
        fclose(fp);
        
    }
    else
    {
        cout<<"Problem with file open."<<endl;
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
