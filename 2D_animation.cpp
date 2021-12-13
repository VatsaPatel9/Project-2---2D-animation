#include <iostream>

#include<stdio.h>
#include <sstream>

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;
int dino_x, dino_y;
int girl_x, girl_y;
int X1, Y1, X2, Y2, diff_x, diff_y, giff_x, giff_y;
bool drag_dino = false, drag_girl = false;


vector<array<int, 2>> dino_co;
vector<array<int, 2>> girl_co;

Mat dinoRunning(Mat back_image, int i, int right, int up, vector<String> filenames, vector<String> dinoColor)
{
	Mat dinoImage;
	Mat dinoMask;

	// Get all jpg in the folder


	/*for (size_t i = 0; i < filenames.size(); i++)
	{
		dinoImage = imread(filenames[i]);


	}*/

	dinoMask = imread(filenames[i]);
	dinoImage = imread(dinoColor[i]);
	uchar blue;
	uchar green;
	uchar red;
	dino_co.clear();
	for (int y = 0; y < dinoMask.rows; y++)
	{
		for (int x = 0; x < dinoMask.cols; x++)
		{
			uchar blue = dinoMask.ptr<uchar>(y)[x * 3 + 0];
			uchar green = dinoMask.ptr<uchar>(y)[x * 3 + 1];
			uchar red = dinoMask.ptr<uchar>(y)[x * 3 + 2];


			if (((blue + green + red)) == 0)
			{
				continue;
			}
			else
			{


				dino_x = (x + right + diff_x);
				dino_y = (y + 200 + up + diff_y);

				if (dino_y < 800 && dino_y>220)
				{

					back_image.ptr<uchar>(dino_y)[(dino_x) * 3 + 0] = dinoImage.ptr<uchar>(y)[x * 3 + 0];
					back_image.ptr<uchar>(dino_y)[(dino_x) * 3 + 1] = dinoImage.ptr<uchar>(y)[x * 3 + 1];
					back_image.ptr<uchar>(dino_y)[(dino_x) * 3 + 2] = dinoImage.ptr<uchar>(y)[x * 3 + 2];
					dino_co.push_back({ (dino_y),(dino_x) });
				}
			}
		}
	}



	return back_image;

}

Mat girlRunning(Mat back_image, int i, int right, int up, vector<String> filenames, vector<String> girlColor)
{
	Mat girlImage;
	Mat girlMask;

	/*for (size_t io = 0; io < filenames.size(); io++)
	{
		cout << filenames[io];


	}*/

	girlMask = imread(filenames[i]);
	girlImage = imread(girlColor[i]);
	uchar blue;
	uchar green;
	uchar red;
	int xB = 300;

	for (int y = 0; y < girlMask.rows; y++)
	{
		for (int x = 0; x < girlMask.cols; x++)
		{
			uchar blue = girlMask.ptr<uchar>(y)[x * 3 + 0];
			uchar green = girlMask.ptr<uchar>(y)[x * 3 + 1];
			uchar red = girlMask.ptr<uchar>(y)[x * 3 + 2];


			if (((blue + green + red)) == 0)
			{
				continue;
			}
			else
			{

				girl_x = (x + 400 + right + giff_x);
				girl_y = (y + 220 + up + giff_y);

				if (girl_y < 800 && girl_y>220)
				{
					back_image.ptr<uchar>(girl_y)[(girl_x) * 3 + 0] = girlImage.ptr<uchar>(y)[x * 3 + 0];
					back_image.ptr<uchar>(girl_y)[(girl_x) * 3 + 1] = girlImage.ptr<uchar>(y)[x * 3 + 1];
					back_image.ptr<uchar>(girl_y)[(girl_x) * 3 + 2] = girlImage.ptr<uchar>(y)[x * 3 + 2];
					girl_co.push_back({ (girl_y),(girl_x) });
				}

			}

		}

	}




	return back_image;

}

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		for (int i = 0; i < dino_co.size(); i++)
		{
			if (y == dino_co[i][0])
			{
				if (x == dino_co[i][1])
				{

					drag_dino = true;
					Y1 = dino_co[i][0];
					X1 = dino_co[i][1];

				}
			}
		}

		for (int i = 0; i < girl_co.size(); i++)
		{
			if (y == girl_co[i][0])
			{
				if (x == girl_co[i][1])
				{
					drag_girl = true;
					Y2 = girl_co[i][0];
					X2 = girl_co[i][1];

				}
			}
		}
	}
	if (drag_dino)
	{


		diff_x = x - X1;
		diff_y = y - Y1;
	}
	if (drag_girl)
	{
		giff_x = x - X2;
		giff_y = y - Y2;

	}
	if (event == EVENT_LBUTTONUP)
	{
		if (drag_girl)
		{

			//girl_co.clear();
			drag_girl = false;
		}
		if (drag_dino)
		{
			//dino_co.clear();
			drag_dino = false;

		}


	}

}



int main(int argc, char** argv)
{
	int i = 0;
	Mat img;
	Mat back_image;

	int right = 0;
	int up = 0;
	vector<String> girlNames;
	vector<String> girlColor;
	vector<String> dinoNames;
	vector<String> dinoColor;
	char filenames[200];
	for (int i = 0; i < 13; i++)
	{
		sprintf_s(filenames, "../dinosaur_mask_%02d.bmp", i);
		dinoNames.push_back(filenames);
		sprintf_s(filenames, "../dinosaur%02d.jpg", i);
		dinoColor.push_back(filenames);
		sprintf_s(filenames, "../girl_mask_%02d.bmp", i);
		girlNames.push_back(filenames);
		sprintf_s(filenames, "../girl%02d.jpg", i);
		girlColor.push_back(filenames);

	}

	img = imread("../bg_scene.jpg");


	int x1ordinate = 5;

	while (true)
	{
		if ((x1ordinate - back_image.rows) == 0)
		{
			x1ordinate = 5;

		}
		else
		{

			back_image.create(img.rows, img.rows, CV_8UC3);
			img(Range(0, 800), Range(0, x1ordinate)).copyTo(back_image(Range(0, 800), Range((back_image.rows - x1ordinate), (back_image.rows - 0))));
			img(Range(0, 800), Range(x1ordinate, img.rows)).copyTo(back_image(Range(0, 800), Range(0, back_image.rows - x1ordinate)));



		}

		setMouseCallback("img", onMouse);
		back_image = girlRunning(back_image, i, right, up, girlNames, girlColor);
		back_image = dinoRunning(back_image, i, right, up, dinoNames, dinoColor);
		//cout << dinoImage.rows << "         " << dinoImage.cols << endl;
		imshow("img", back_image);

		char b = waitKey(5);
		if (b == 100 || b == 68)
			right = right + 5;
		if (b == 97 || b == 65)
			right = right - 5;
		if (b == 87 || b == 119)
		{
			if (up <= 0)
			{
				up = 0;
				continue;
			}
			else
				up = up - 5;
		}
		if (b == 83 || b == 115)
		{
			if (up >= 390)
			{
				up = 390;
				continue;
			}
			else
				up = up + 5;
		}

		if (b == 27)
			break;
		if (i < (girlNames.size() - 1))
		{
			i = i + 1;
		}
		else
		{
			i = 0;
		}

		x1ordinate += 5;
	}



	return 1;
}
