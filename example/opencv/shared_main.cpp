
#include <memory>
#include <iostream>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// 레퍼런스 카운트를 증가시키는 방법.
// 1. 함수의 인자로 넘기거나 값의 대입으로 인한 복사가 일어나야 한다.
// 2. 오직 shared_ptr 타입으로 대입이 일어났을 때만 카운트가 증가한다.
// 3. 레퍼런스를 넘길 경우 카운트가 증가하지 않는다 (unique_ptr 과 비교)

void printCounts(std::shared_ptr<cv::Mat> _sptr)
{
    std::cout << "counts: " << _sptr.use_count() << std::endl;
}

std::shared_ptr<cv::Mat> toCvNot(std::shared_ptr<cv::Mat> _sptr)
{
    std::cout << "counts: " << _sptr.use_count() << std::endl; // 1
    printCounts(_sptr); // 2
    printCounts(_sptr); // 2
    
    cv::Mat dst(*_sptr);

    for (int x = 0; x < _sptr->cols; x++)
    {
        for (int y = 0;  y < _sptr->rows; y++)
        {
            dst.at<cv::Vec3b>(y, x)[0] = 255 - _sptr->at<cv::Vec3b>(y, x)[0];
            dst.at<cv::Vec3b>(y, x)[1] = 255 - _sptr->at<cv::Vec3b>(y, x)[1];
            dst.at<cv::Vec3b>(y, x)[2] = 255 - _sptr->at<cv::Vec3b>(y, x)[2];
        }
    }

    std::shared_ptr<cv::Mat> sptr = std::make_shared<cv::Mat>(dst);

    std::cout << "after" << std::endl;
    printCounts(_sptr); // 2

    return sptr;
}

int main()
{
    cv::Mat img = cv::imread("/home/colson/workspace/cpp-memory-master/example/opencv/landscape.jpg", cv::IMREAD_COLOR);
    std::shared_ptr<cv::Mat> sptr1(new cv::Mat(img));
    std::cout << "col: " << img.cols << "row: " << img.rows << std::endl;
    cv::imshow("Display window", img);
    int k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/andscape_copy.png", img);

    std::shared_ptr<cv::Mat> sptr2 = toCvNot(std::move(sptr1));
    std::cout << "out" << std::endl;
    printCounts(sptr1); // 0
    std:: cout << "counts: "<< sptr2.use_count() << std::endl;
    printCounts(sptr2); // 2
    
    cv::imshow("NotCV window", *sptr2);
    k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/shared_not.png", *sptr2);
    
    std::shared_ptr<cv::Mat> sptr3 = std::make_shared<cv::Mat>(img);
    printCounts(sptr3); // 2
    std::shared_ptr<cv::Mat> sptr4 = sptr3; // 3과 4는 같은곳을 가르킨다.
    printCounts(sptr3); // 3
    printCounts(sptr4); // 3
    sptr4.reset();
    printCounts(sptr3); // 0
    printCounts(sptr4); // 0
    
    return 0;
}