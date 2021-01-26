using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;

namespace NNDataFiller.MNIST
{
    public struct MNIST_Digit
    {
        public Bitmap bitmap;
        public byte label;

        public MNIST_Digit(Bitmap bitmap, byte label)
        {
            this.bitmap = bitmap;
            this.label = label;
        }
    }
    public static class MNIST_Digits
    {
        private const int IMG_FILE_MAGIC_INT = 2051;
        private const int LABEL_FILE_MAGIC_INT = 2049;

        private static Int32 ReverseBytes(Int32 value)
        {
            return (value & 0x000000FF) << 24 | (value & 0x0000FF00) << 8 | (value & 0x00FF0000) >> 8 | (int)((value & 0xFF000000) >> 24);
        }

        private static Int32 ReadInt32Reversed(BinaryReader reader)
        {
            return ReverseBytes(reader.ReadInt32());
        }

        public static void ToDataFillerAndBitmap(List<MNIST_Digit> data, out DataFiller dataFiller, out Bitmap bitmap, int width = 100, int maxCount=0)
        {
            if(data==null || data.Count==0)
            {
                dataFiller = null;
                bitmap = null;
            }

            if(width < 0)
            {
                width = 1;
            }

            if (maxCount <= 0)
            {
                maxCount = data.Count;
            }

            Size imgSize = data[0].bitmap.Size;

            int realCount = Math.Min(maxCount, data.Count);



            int maxWidth = Math.Min(width, data.Count) * imgSize.Width;
            int maxHeight = imgSize.Height * (realCount / width + ((realCount % width == 0) ? 0 : 1));

            bitmap = new Bitmap(maxWidth, maxHeight);

            dataFiller = new DataFiller(imgSize, 10);

            Point currPos = Point.Empty;
            for (int i = 0; i < realCount; i++)
            {
                if(currPos.X >= maxWidth)
                {
                    currPos.Y += imgSize.Height;
                    currPos.X = 0;
                }
                using (Graphics grD = Graphics.FromImage(bitmap))
                {
                    grD.DrawImage(data[i].bitmap, new Rectangle(currPos, imgSize), new Rectangle(Point.Empty, imgSize), GraphicsUnit.Pixel);
                }

                double[] outputs = new double[10];
                outputs[data[i].label] = 1;
                dataFiller.Add(currPos, outputs);

                currPos.X += imgSize.Width;
            }
        }

        public static List<MNIST_Digit> Read(BinaryReader images, BinaryReader labels, int maxCount=0)
        {
            if (ReadInt32Reversed(images) != IMG_FILE_MAGIC_INT)
            {
                throw new Exception("Wrong images file format");
            }
            if (ReadInt32Reversed(labels) != LABEL_FILE_MAGIC_INT)
            {
                throw new Exception("Wrong labels file format");
            }

            int imagesCount = ReadInt32Reversed(images);
            int labelsCount = ReadInt32Reversed(labels);

            if(imagesCount!=labelsCount)
            {
                throw new Exception("Different size of labels and images");
            }

            if (maxCount <= 0)
            {
                maxCount = imagesCount;
            }

            List<MNIST_Digit> _data = new List<MNIST_Digit>(Math.Min(maxCount, imagesCount));

            int rows = ReadInt32Reversed(images);
            int cols = ReadInt32Reversed(images);

            for (int i = 0; i < imagesCount && i < maxCount; i++)
            {
                MNIST_Digit digit = new MNIST_Digit();
                digit.bitmap = new Bitmap(rows, cols);
                for (int y = 0; y < cols; y++)
                {
                    for (int x = 0; x < rows; x++)
                    {
                        byte color = (byte)(255 - images.ReadByte());
                        digit.bitmap.SetPixel(x, y, Color.FromArgb(color, color, color));
                    }
                }
                digit.label = labels.ReadByte();
                _data.Add(digit);
            }

            return _data;
        }


    }
}
