void resize(int nWidth,int nHeight){
	Mat temp(nHeight,nWidth,CV_8UC3,Scalar(0,0,0));
	
	double xr=matrix.rows/(double)w1;
	double yr=matrix.cols/(double)h1;
	int px,py;
	for(int y=0; y<temp.rows;y++){
		for(int x=0;x<temp.cols;x++){
		px=x*xr;
		py=y*yr;
		temp.at<Vec3b>(Point(x,y))=testMatrix.at<Vec3b>(Point(px,py));
		}
	}

	testMatrix=temp;


}
