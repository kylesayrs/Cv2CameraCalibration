#include <iostream>
#include <format>
#include <opencv2/opencv.hpp>
#include "threadpool.h"


float get_focus_factor(cv::Mat frame) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    cv::Mat laplacian;
    cv::Laplacian(gray, laplacian, CV_64F);

    cv::Scalar mean, std;
    cv::meanStdDev(laplacian, mean, std);
    return std.val[0] * std.val[0];
}


int main(int argc, char **argv) {
    // validate arguments
    if (argc != 2) {
        std::cerr << "Usage: ccc <video file path>" << std::endl;
        return -1;
    }
    std::string video_path = argv[1];
 
    // open video
    cv::VideoCapture video_capture = cv::VideoCapture(video_path);
    if (!video_capture.isOpened()) {
        std::cerr << "Error: Could not open video file " << video_path << std::endl;
        return -1;
    }

    // read frames from video
    cv::Mat frame;
    unsigned frame_count = 0;
    while (video_capture.read(frame)) {

        char window_name[100];
        std::snprintf(
            window_name,
            sizeof(window_name) / sizeof(char),
            "Frame{:03d}\n",
            frame_count
        );
        cv::imshow(window_name, frame);
        cv::waitKey(0);

        float focus_factor = get_focus_factor(frame);
        std::cout << focus_factor << std::endl;
        


        frame_count++;
    }
}
