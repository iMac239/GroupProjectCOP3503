int maxLength=30;

bool checkColor(int *checkColorValues,int bValue, int gValue, int rValue){
	int rDifference= abs(checkColorValues[2]-rValue); //Find absolute difference in rValues
	int gDifference=abs(checkColorValues[1]-gValue); //Find absolute difference in gValues
	int bDifference=abs(checkColorValues[0]-bValue); //Find absolute difference in bValues;
	if((rDifference<=maxLength)&&(gDifference<=maxLength)&& (bDifference<=maxLength)){    // Checks to see if the r is in the box [30,30,30]
		return true;
	}
	return false;
};

void focusColor (int colorOption){
	for(int y=0; y<testMatrix.rows;y++){
             for(int x=0; x<testMatrix.cols;x++){
                 Vec3b color=testMatrix.at<Vec3b>(Point(x,y));
                 if(!checkColor(colorArray[colorOption],color[0],color[1],color[2])){
					int grayValue=grayScale(color[0],color[1],color[2]);
					color[0]=grayValue;
					color[1]=grayValue;
					color[2]=grayValue;
					testMatrix.at<Vec3b>(Point(x,y))=color;
				 }
             }
	}
};
  



/* Creates Array
	int **colorArray;
	int numberOfColors=20;
	colorArray=new int*[numberOfColors];
	for(int i=0; i<numberOfColors;i++){colorArray[i]=new int[3];}
	for(int i=0; i<numberOfColors;i++){
	for(int j=0;j<3;j++){
			colorArray[i][j]=0;
			}
	}
//RED
colorArray[0][0]=0;
colorArray[0][1]=0;
colorArray[0][2]=255;

//Blue
colorArray[1][0]=255;
colorArray[1][1]=0;
colorArray[1][2]=0;

//Green
colorArray[2][0]=0;
colorArray[2][1]=255;
colorArray[2][2]=0;

//Cyan
colorArray[3][0]=255;
colorArray[3][1]=255;
colorArray[3][2]=0;

//Yellow
colorArray[4][0]=0;
colorArray[4][1]=255;
colorArray[4][2]=255;

//Magenta
colorArray[5][0]=255;
colorArray[5][1]=255;
colorArray[5][2]=255;

//Orange
colorArray[6][0]=0;
colorArray[6][1]=128;
colorArray[6][2]=255;
*/
