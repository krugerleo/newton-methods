double calculaNorma(double *X,int n){
    double max=abs(X[0]);
    for(int i = 0; i < n;++i){
        double a = abs(X[i]);
        if(max < a )
            max= a;
    }
    return max;
};