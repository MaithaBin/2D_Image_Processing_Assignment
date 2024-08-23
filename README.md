# 2D Image Processing: Final Assignment

## Attachments
 - README.txt
 - Short_Report.pdf
 - Final_Project\Final_Project\Coin_detection.cpp(source code)
 - Final_Project\x64\Release\testing_dataset(imput images)
 - Final_Project\x64\Release\output(output images)
 - Final_Project\x64\Release\Output.txt

## Development Environment
 - OS:Windows10
 - Visual Studio 2019
 - OpenCV4.5.0
 - Release x64

## How To Complie the Program
1. After downloading the "Final_Project", open Final_Project.sln on Visual Studio.
2. Change the setting as following:
   - Open [Project > Final_Project Properties].
   - Set OpenCV directories depending on your development environment.
     [Configuration Properties > VC++ Directories] 
	- Include Directories (e.g. C:\opencv4.5.0\build\include)
	- Library Directories (e.g. C:\opencv4.5.0\build\x64\vc15\lib)
   - [Configuration Properties > Linker >General]
        - AdditionalLibraryDirectories (e.g. C:\opencv4.5.0\build\x64\vc15\lib)
   - [Configuration Properties > Linker > Input]
        - Additional Dependencies (e.g. opencv_world450.lib;opencv_world450d.lib;)
3. Apply the new setting and press OK.
4. Set [Release] and [x64](depending on your environment). 
Then you can complie the program.
Note: If you are a macOS or Linux user, you might need to change some "#including <header>" lines.

## How To Run the Application
1. Open [Tools > Command line > Developer PowerShell].
2. Move the current directory to "x64\Release", using the following command as your reference.
 cd .\x64\Release\
3. Run the application.
 .\Final_Project.exe
4. Input a dataset name.
e.g.) testing_dataset\testdata1.jpg
5. Press X button if each output image shows up.
6. You can find the output images in "output" folder and an annotation(Output.txt).

## How the Application works
When you run the program and it reads the image on the left, it detects coins on the right.
![CoinDetection](https://github.com/user-attachments/assets/8e11ebc7-7c0d-404d-9613-ce9458dae707)

After it's done, you can see the output.txt showing the number of coins in the picture.
To follow the assigment tasks, the output.txt also shows the details related to its radious and its center position.
```
testing_dataset\testdata1.jpg
   x =  139  y =  115  radius =  36
   x =  257  y =  235  radius =  40
   x =  325  y =  189  radius =  40
   x =  191  y =  183  radius =  41
   x =  187  y =  253  radius =  30
   x =  219  y =  103  radius =  40
   x =  259  y =  163  radius =  30
   x =  305  y =  119  radius =  29
   x =  323  y =  255  radius =  31
Number of coins : 9
```

## Note
- If necessary, you can remove the old "Output.txt". Otherwise, the result will be added the last line of the file.

