
#include <opencv2/imgproc/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O
#include <opencv2/core/mat.hpp>
#include <opencv2\core\operations.hpp>
#include "opencv2/objdetect/objdetect.hpp"

typedef struct {
	double **Data;
	int numPoints;
	int numFeatures;
} dataset_t;

using namespace cv;

int* kmeans(dataset_t *dataset, double*** C, int k, int iter);
int* meanshift(dataset_t* Dataset, int h);
Mat transfrom(Mat I, float alpha, float scaleFactors[2], float shear[2], float trans[2]);
dataset_t* scaleDataset(dataset_t *dataset);

int partition(float *data, int left, int right, int pivotIndex);
void quicksort(float *data,int left, int right);

void merge_sort(float* data);


int mainzz(int argc, char *argv[])
{


	  VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat detection;
    namedWindow("edges",1);

	String face_cascade_name = "C:/Users/gio/Documents/Visual Studio 2012/Projects/ConsoleApplication1/Debug/lbpcascade_frontalface.xml";
	String eyes_cascade_name = "C:/Users/gio/Documents/Visual Studio 2012/Projects/ConsoleApplication1/Debug/haarcascade_eye_tree_eyeglasses.xml";
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	 if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, frame, CV_BGR2GRAY);
//		equalizeHist(frame,frame);
		std::vector<Rect>faces;
		face_cascade.detectMultiScale(frame,faces, 1.1, 2, 0, Size(80, 80) );

		for( int i = 0; i < faces.size(); i++ )
    {
      Mat faceROI = frame( faces[i] );
      std::vector<Rect> eyes;

      //-- In each face, detect eyes
      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
      if( eyes.size() == 2)
      {
     //    //-- Draw the face
         Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
         ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

     for( int j = 0; j < eyes.size(); j++ )
      { //-- Draw the eyes
        Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 ); 
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, center, radius, Scalar( 255, 0, 255 ), 3, 8, 0 );
          }
	 
       }
        
       
    }
		
		imshow("edges", frame);
        if(waitKey(30) >= 0) break;
	}
    // the camera will be deinitialized automatically in VideoCapture destructor
    //return 0;

	//float data[9] = {3,7,8,5,2,1,9,5,4};
	//quicksort(data,0,8);
	//merge_sort(data);
	
//	dataset_t* Dataset = (dataset_t*)malloc(sizeof(dataset_t));
//	printf("%s",argv[1]);
//	Mat I = cvLoadImage("C:/Users/gio/Documents/Visual Studio 2012/Projects/ConsoleApplication1/Debug/test.jpg",1);
//	
//	//populate dataset with image pixels
//	cvNamedWindow("input");
//	imshow("input",I);
//	cvWaitKey(0);
//	int nRows = I.rows;
//	int nCols = I.cols*I.channels();
//	
//
//	Dataset->numFeatures = I.channels()+2;
//	Dataset->numPoints = I.rows*I.cols;
//
//	Dataset->Data = (double**)malloc(Dataset->numPoints*sizeof(double*));
//	for (int i=0; i<Dataset->numPoints;i++)
//		Dataset->Data[i] = (double*)malloc(Dataset->numFeatures*sizeof(double));
//
//	int row, col;
///*	for (row = 0; row<Dataset->numPoints;row++){
//		for (col = 0; col<Dataset->numFeatures;col++){
//			Dataset->Data[row][col] = rand() / (double)RAND_MAX;
//		}
//	}*/
//
//	
//	
//	int npoint = 0;
//    for( row = 0; row < nRows; row++)
//    {
//        
//		for ( col = 0; col < nCols; col=col+I.channels())
//        {
//			
//			Dataset->Data[npoint][1] = (float) I.ptr<uchar>(row)[col];
//			Dataset->Data[npoint][2] = (float) I.ptr<uchar>(row)[col+1];
//			Dataset->Data[npoint][3] = (float) I.ptr<uchar>(row)[col+2];
//			Dataset->Data[npoint][4] = row;
//			Dataset->Data[npoint][5] = col;
//			npoint++;
//        }
//    }
//
//	dataset_t* sDataset = scaleDataset(Dataset);
//	int k = 3;
//	double **C = NULL;
//	int* labels = kmeans(sDataset, &C, 3,100);
//	
//	//create output image
//	Mat outImage(I.size(),CV_8UC3);
//	
//	int pointcnt = 0;
//	for (int row = 0; row< nRows;row++)
//		for (int col = 0; col<outImage.cols*outImage.channels(); col=col+outImage.channels()){
//			(uchar)outImage.ptr<uchar>(row)[col]= 0 ;
//			(uchar)outImage.ptr<uchar>(row)[col+1]= 0 ;
//			(uchar)outImage.ptr<uchar>(row)[col+2]= 0 ;
//			(uchar)outImage.ptr<uchar>(row)[col+labels[pointcnt]]= 255 ;
//			pointcnt++;
//		}
//
//	cvNamedWindow("output");
//	imshow("output",outImage);
//	cvWaitKey(0);
//	float scale[2] ={1,1};
//	float shear[2] = {0,0};
//	float trans[2] = {0,0};
//	transfrom(I, 0., scale, shear, trans);
//

		
	return 0;
}


int* meanshift(dataset_t* Dataset, int h){
	
	return 0;
}


int* kmeans(dataset_t* Dataset, double*** C, int k, int iter){
	if (*C == NULL){
		
		//initialize random centroids
		free (*C);
		*C = (double**)calloc(k,sizeof(double*));
		for (int i = 0; i < k; i++){
			(*C)[i] = (double*)calloc(Dataset->numFeatures,sizeof(double));

			for (int j = 0; j<Dataset->numFeatures;j++)
				(*C)[i][j] = (double)rand()/(double)RAND_MAX;
		}

	}

	double minDist, tmpDist;
	int minK;
	int* labels = (int*)malloc(Dataset->numPoints*sizeof(int)); 
	int* numSamplesC = (int*)calloc(k,sizeof(int)); 
	
	double** cMeans = (double**)calloc(k,sizeof(double*));
	for (int j = 0; j<k;j++)
		cMeans[j] = (double*)calloc(Dataset->numFeatures,sizeof(double));

	int T = 0;
	int moved = 1;
	while (T < iter && moved==1){
		T++;
		printf("iteration %d \n", T);
		// step 1 - compute membership
		for (int point = 0; point<Dataset->numPoints;point++){
			minDist = 1e10;
			minK = -1;
			for (int cluster = 0; cluster<k;cluster++){
				//measure Euclidean distance between datapoint and cluster 
				tmpDist = 0;
				for (int f = 0; f<Dataset->numFeatures;f++){
					//printf("%lf \n", Dataset->Data[point][f]);
					//printf("%lf \n",(*C)[cluster][f]);
					tmpDist += ((*C)[cluster][f] - Dataset->Data[point][f])*((*C)[cluster][f] - Dataset->Data[point][f]);
				}
				tmpDist = std::sqrt(tmpDist);
				//printf("Dist: %f ; Point: %d; Cluster: %d \n", tmpDist, point,cluster);
				if (tmpDist < minDist){
					minDist = tmpDist;
					minK = cluster;
				}
			}
			labels[point] = minK;
			numSamplesC[minK]++;
			for (int f=0;f<Dataset->numFeatures;f++)
				cMeans[minK][f] += Dataset->Data[point][f]; 
			
			//printf("%d \n",labels[point]);
		}

		//update centroids
		double prevC;
		moved = 0;
		for (int c=0;c<k;c++)
			for (int f=0;f<Dataset->numFeatures;f++){
				prevC = (*C)[c][f];
				(*C)[c][f] = cMeans[c][f] / numSamplesC[c]; 
				if (prevC != (*C)[c][f])
					moved = 1;
			}
	}
	return labels;     
}


//Pixel filling with backward mapping
Mat transfrom(Mat I, float alpha, float scaleFactors[2], float shear[2], float trans[2]){
	//compute grid extrema
	int point_br[2] = {I.rows-1,0};
	int width = I.cols;
	int height = I.rows;
	//check T diagonal
	if (scaleFactors[0] != 1)
		height *= scaleFactors[0];
	if (scaleFactors[1] != 1)
		width *= scaleFactors[1];


	//create inverse transform matrix
	float T[3][3] = { {cos(alpha)/scaleFactors[0], sin(alpha)-shear[0], -trans[0]} , 
					  {-shear[1]-sin(alpha), cos(alpha)/scaleFactors[1], -trans[1] }, 
	                  { 0, 0, 1} };

	Mat outImage(height,width,CV_8UC(I.channels()));
	// compute pixel grid
	float p[2],d1,d2,v1,v2,v;
	
	int x1,x2,y1,y2;
	
	for (int row = 0; row< outImage.rows; row++){
		for (int col = 0; col< outImage.cols; col++){
			//compute point from input image
			//orig point [row col 1]'
			for (int pp=0 ; pp<2;pp++)
				p[pp] = row*T[pp][0] +  col*T[pp][1] + T[pp][2];
			//printf("Orig point: %d,%d -- backward mapping: %f %f \n",row,col,p[0],p[1]);
			
			//compute the closest point to p on the grid of image I 
			x1 = floor(p[0]);
			x2 = ceil(p[0]);
			y1 = floor(p[1]);
			y2 = ceil(p[1]);
			d1 = (x2 - p[0])/(x2-x1);
			d2 = (p[0]-x1)/(x2-x1);
			printf("Orig point: %f,%f %f %f \n",x1,y1,x2,y2);
			for (int c = 0;c<3;c++){
				v1 = d2*(uchar)I.ptr<uchar>(x1)[y1*I.channels()+c] + d1*(uchar)I.ptr<uchar>(x1)[y2*I.channels()+c];
				v2 = d2*(uchar)I.ptr<uchar>(x2)[y1*I.channels()+c] + d1*(uchar)I.ptr<uchar>(x2)[y2*I.channels()+c];

				d1 = (y2 - p[1])/(y2-y1);
				d2 = (p[1]-y1)/(y2-y1);
				v = d1*v2 + d2*v1;
				printf("pixel value: %f\n",v);
				(uchar)outImage.ptr<uchar>(row)[col*outImage.channels()+c]= (uchar)v;
			}
			
			
		}

		}
	
	imshow("copy",outImage);
	cvWaitKey(0);
	return outImage;
}

//scale dataset in 0-1 range
dataset_t* scaleDataset(dataset_t *dataset){
	dataset_t* scaledDataset = (dataset_t*)malloc(sizeof(dataset_t));
	scaledDataset->numFeatures = dataset->numFeatures;
	scaledDataset->numPoints = dataset->numPoints;
	
	scaledDataset->Data = (double**)malloc(scaledDataset->numPoints*sizeof(double*));
	for (int i=0; i<scaledDataset->numPoints;i++)
		scaledDataset->Data[i] = (double*)malloc(scaledDataset->numFeatures*sizeof(double));

	
	//find min & max for each feature
	for (int f = 0; f<dataset->numFeatures; f++){
		double minF = 1e10;
		double maxF = -1e10;
		
		for (int p = 0; p<dataset->numPoints; p++){
			if (dataset->Data[p][f] < minF)
				minF = dataset->Data[p][f];
			else if (dataset->Data[p][f] > maxF)
				maxF = dataset->Data[p][f];
		}
		
		//scale features
		for (int p = 0; p<dataset->numPoints; p++){
			scaledDataset->Data[p][f] = (dataset->Data[p][f] - minF) / (maxF - minF);
		}
	}

	return scaledDataset;
		
}

int partition(float* data, int left, int right, int pivotIndex){
	float pivot = data[pivotIndex];

	printf("Pivot: %f \n Presorting: \n",pivot);
	for (int i=left;i<=right;i++)
		printf("%f ",data[i]);
	printf("\n");

	//switch pivot and rightmost element
	float tmp = data[right];
	data[right] = pivot;
	data[pivotIndex] = tmp;
	//split array in two subarrays
	int index = left;
	for (int i=left;i<right;i++){
		//if (index != i)
			if (data[i] < pivot){
		
				printf("Before - index: %d \n",index);
				for (int i=left;i<=right;i++)
					printf("%f ",data[i]);
				printf("\n");

				tmp = data[i];
				data[i] = data[index];
				data[index] = tmp;
				index++;

				printf("After - index: %d \n",index);
				for (int i=left;i<=right;i++)
					printf("%f ",data[i]);
				printf("\n");
			}
			
		
	}
	tmp = data[index];
	data[index] = pivot;
	data[right] = tmp;

	printf("Pivot: %f \n Post-sorting: \n",pivot);
	for (int i=left;i<=right;i++)
		printf("%f ",data[i]);
	printf("\n");


	return index;
}

void quicksort(float *data, int left, int right){
	if (left < right){
		int pivotIndex = left+( (right-left)/2);
		printf("pivot index: %d \n",pivotIndex);
		int newPivotIndex = partition(data,left,right,pivotIndex);

		printf("\n Post-sorting: \n");
		for (int i=left;i<=right;i++)
			printf("%f ",data[i]);
		printf("\n");

		quicksort(data,left, newPivotIndex-1);
		quicksort(data, newPivotIndex+1,right);
	}

}

void merge_sort(float *list, int len){

	int m = len/2;

	float *left;

}