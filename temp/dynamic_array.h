//dynamic_array.h
//version 0.1

#ifndef _DYNAMIC_ARRAY_

void **Matrix2D(int nrows,int  ncols,int element_size, int first_row=0, int first_col=0) 
{ 
//nrows and ncols are the total number of rows and columns,first_row and first_col are the starting rows and columns(default is 0,it can be negative too !!) 
  void **p; 
  int alignment; 
  long i; 

  if(nrows < 1 || ncols < 1) return(NULL); 
  i = nrows*sizeof(void *); 
  //  align the addr of the data to be a multiple of sizeof(long double),this helps easy fetching and fast processing in some processors 
  alignment = i % sizeof(long double); 
  if(alignment != 0) alignment = sizeof(long double) - alignment; 
  i += nrows*ncols*element_size+alignment; 
  p = (void **)new((size_t)i); 

  if(p!= NULL) 
  { 
    //compute the address of matrix[first_row][0] 
    p[0] = (char *)(p+nrows)+alignment-first_col*element_size; 
    for(i = 1; i < nrows; i++) 
      // compute the address of matrix[first_row+i][0] 
      p[i] = (char *)(p[i-1])+ncols*element_size; 
    //compute the address of matrix[0][0] 
    p -= first_row; 
  } 
  else 
      //cout<<"Memory allocation failure"<<endl; 
	  exit(-20);

return(p); 
}
#else
extern void **Matrix2D(int nrows,int  ncols,int element_size, int first_row=0, int first_col=0);
#endif

//code snippet below is simple version
/*
char *Pointer; 
    int *array_contig; 
    int **array_2d; 
    int i; 
     
    Pointer = (char *) malloc(x*sizeof(int*)+x*y*sizeof(int)); 

    array_contig = (int *)(Pointer + x * sizeof (int *)); 
     // equivalent is   array_contig = ((int *)Pointer) + x; 
    array_2d = (int **)Pointer; 
    for (i = 0; i < x; ++i) 
    { 
         array_2d[i] = array_contig + i * y; 
    } 
*/