
#include <memory>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

std::unique_ptr<cv::Mat> toGray(std::unique_ptr<cv::Mat> _uptr)
{
    std::cout << __func__ << "using unique ptr" << std::endl;
    cv::Mat dst;
    cv::cvtColor(*_uptr, dst, cv::COLOR_RGB2GRAY);
    std::unique_ptr<cv::Mat> ret(new cv::Mat(dst));
    return ret;
}

cv::Mat toGray(cv::Mat* _ptr)
{
    std::cout << __func__ << "using raw ptr" << std::endl;
    cv::Mat dst;
    cv::cvtColor(*_ptr, dst, cv::COLOR_RGB2GRAY);
    return dst;
}

std::unique_ptr<cv::Mat> toEdge(std::unique_ptr<cv::Mat> _uptr)
{
    std::cout << __func__ << "using unique ptr" << std::endl;
    cv::Mat dst;
    cv::Canny(*_uptr, dst, 100, 127);
    std::unique_ptr<cv::Mat> ret(new cv::Mat(dst));
    std::unique_ptr<cv::Mat> A;
    A = std::make_unique<cv::Mat>(dst);
    return A;
}

std::unique_ptr<cv::Mat> toEdge(cv::Mat* _ptr)
{
    std::cout << __func__ << "using raw ptr" << std::endl;
    cv::Mat ret;
    cv::Canny(*_ptr, ret, 100, 200);
    std::unique_ptr<cv::Mat> dst(new cv::Mat(ret));
    return dst;
}

int main()
{
    cv::Mat img = cv::imread("/home/colson/workspace/cpp-memory-master/example/opencv/landscape.jpg", cv::IMREAD_COLOR);
    
    std::unique_ptr<cv::Mat> uptr1(new cv::Mat(img));

    std::cout << "col: " << img.cols << "row: " << img.rows << std::endl;
    cv::imshow("Display window", img);
    int k = cv::waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/unique_landscape_copy.png", img);

    cv::Mat gray = toGray(&img);
    cv::imshow("Gray window1", gray);
    k = cv::waitKey(0);
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/unique_landscape_Gray.png", gray);

    auto ret = toGray(std::move(uptr1));
    cv::Mat *retptr = ret.get();
    cv::imshow("Gray window2", *retptr);
    k = cv::waitKey(0);
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/unique_landscape_Gray2.png", *retptr);
    
    // Unique ptr 은 그냥 ptr 처럼 쓸 수 있다. 물론 shared_ptr도 매한가지다.
    std::unique_ptr<cv::Mat> uptr2 = toEdge(retptr);
    cv::imshow("Edge window1", *uptr2);
    k = cv::waitKey(0);
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/unique_landscape_Edge.png", *uptr2);
    
 

    auto B = std::move(ret);
    auto ret2 = toEdge(std::move(B));
    cv::Mat *retptr2 = ret2.get();
    cv::imshow("Edge window2", *retptr2);
    k = cv::waitKey(0);
    if(k == 's')
        cv::imwrite("/home/colson/workspace/cpp-memory-master/example/opencv/images/unique_landscape_Edge2.png", *retptr2);

    return 0;
}