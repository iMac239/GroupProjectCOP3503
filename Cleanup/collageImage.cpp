void collageImage(int numberPerRow, int numberPerCols){
	int thumbNailH=testMatrix.cols/numberPerCols;
	int thumbNailW=testMatrix.rows/numberPerRow;
	resize(thumbNailW,thumbNailH);
	Mat thumbNail=testMatrix.clone();
	testMatrix=matrix.clone();
	for(int y=0; y<thumbNail.rows;y++){
		for(int x=0; x<thumbNail.cols;x++){
			Vec3b color=thumbNail.at<Vec3b>(Point(x,y));
			testMatrix.at<Vec3b>(Point(x,y))=thumbNail.at<Vec3b>(Point(x%thumbNail.cols,y%thumbNail.rows));		
		}
	}
}

