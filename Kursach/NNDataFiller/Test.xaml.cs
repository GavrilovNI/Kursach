using NNDataFiller.MNIST;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace NNDataFiller
{
    /// <summary>
    /// Логика взаимодействия для Test.xaml
    /// </summary>
    public partial class Test : Window
    {
        public Test()
        {
            InitializeComponent();
        }

        List<MNIST_Digit> _data = null;
        int nextID;

        private const string imagesPostfix = "-images.idx3-ubyte";
        private const string labelsPostfix = "-labels.idx1-ubyte";

        private void btn_load_click(object sender, RoutedEventArgs e)
        {
            if (!Utils.GetPathOpen(out string fileName))
                return;

            int cutId = -1;
            cutId = fileName.IndexOf(imagesPostfix);
            if (cutId == -1)
            {
                cutId = fileName.IndexOf(labelsPostfix);
            }

            string filePrefix = (cutId == -1) ? fileName : fileName.Substring(0, cutId);

            if (!File.Exists(filePrefix + imagesPostfix) || !File.Exists(filePrefix + labelsPostfix))
            {
                //files not exist
                return;
            }

            using (BinaryReader writerImages = new BinaryReader(File.Open(filePrefix + imagesPostfix, FileMode.Open)))
            {
                using (BinaryReader writerLabels = new BinaryReader(File.Open(filePrefix + labelsPostfix, FileMode.Open)))
                {

                    _data = MNIST_Digits.Read(writerImages, writerLabels);

                    MNIST_Digits.ToDataFillerAndBitmap(_data, out DataFiller dataFiller, out Bitmap bitmap);

                    bitmap.Save(filePrefix + "-full-image.jpg");


                    if (_data == null)
                    {
                        return;
                    }

                    nextID = 0;
                    label_Count.Content = _data.Count.ToString();
                    SetNextImage();
                }
            }
        }

        private void SetNextImage()
        {
            if(_data==null || _data.Count==0)
            {
                return;
            }

            if (nextID >= _data.Count)
            {
                nextID = 0;
            }

            image.Source = Utils.Bitmap2Source(_data[nextID].bitmap);
            label_Digit.Content = _data[nextID].label.ToString();

            label_Num.Content = nextID.ToString();
            nextID++;
        }

        private void btn_next_click(object sender, RoutedEventArgs e)
        {
            SetNextImage();
        }
    }
}
