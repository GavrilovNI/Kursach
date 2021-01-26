using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace NNDataFiller
{
    public class Utils
    {
        public static bool LoadImage(out Bitmap image)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            dlg.DefaultExt = ".png";
            dlg.Filter = "All images(.jpeg;*.jpg;*.png;*.ppm)|*.jpeg;*.jpg;*.png;*.ppm; " +
                        "|JPEG Files (*.jpeg;*.jpg)|*.jpeg;*.jpg" +
                        "|PNG Files (*.png)|*.png" +
                        "|PPM Files (*.ppm)|*.ppm";
            Nullable<bool> fileDialogResult = dlg.ShowDialog();

            if (fileDialogResult == true)
            {
                image = new Bitmap(dlg.FileName);
                return true;
            }

            image = null;
            return false;
        }

        public static bool GetPathOpen(out string path, string filter = "All|*.*")
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            dlg.Filter = filter;
            Nullable<bool> fileDialogResult = dlg.ShowDialog();

            if (fileDialogResult == true)
            {
                path = dlg.FileName;
                return true;
            }

            path = string.Empty;
            return false;
        }

        public static bool GetPathSave(out string path, string filter = "All|*.*")
        {
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();

            dlg.Filter = filter;
            Nullable<bool> fileDialogResult = dlg.ShowDialog();

            if (fileDialogResult == true)
            {
                path = dlg.FileName;
                return true;
            }

            path = string.Empty;
            return false;
        }


        public static void SaveToFile(DataFiller dataFiller, string filePath)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Open(filePath, FileMode.OpenOrCreate)))
            {
                writer.BaseStream.Position = writer.BaseStream.Length;
                dataFiller.SaveAndClear(writer);
            }
        }

        public static void ChangeWindow(Window curr, Window next, Action onClosingAction=null)
        {
            curr.Hide();
            CancelEventHandler onClosing = null;
            onClosing = (object sender, CancelEventArgs args) => {

                onClosingAction?.Invoke();

                curr.Show();
                next.Closing -= onClosing;
            };
            next.Closing += onClosing;
            next.Show();
        }


        public static string GetNotExistFilePath(string filepath)
        {
            int dotPos = filepath.LastIndexOf(".");
            string prefix = filepath.Substring(0, dotPos);
            string ext = filepath.Substring(dotPos);

            string currFilepath = prefix + ext;
            int x = 1;
            while(File.Exists(currFilepath))
            {
                currFilepath = prefix + "(" + x.ToString() + ")" + ext;
                x++;
            }
            return currFilepath;
        }

        public static bool AskYesNo(string msg)
        {
            MessageBoxResult result = MessageBox.Show(msg, "Question", MessageBoxButton.YesNo, MessageBoxImage.Question);
            return result == MessageBoxResult.Yes;
        }

        public static System.Windows.Media.PixelFormat ConvertPixelFormat(System.Drawing.Imaging.PixelFormat pixelFormat)
        {
            switch(pixelFormat)
            {
                case System.Drawing.Imaging.PixelFormat.Format24bppRgb:
                    return System.Windows.Media.PixelFormats.Bgr24;
                case System.Drawing.Imaging.PixelFormat.Format32bppArgb:
                    return System.Windows.Media.PixelFormats.Bgra32;
                case System.Drawing.Imaging.PixelFormat.Format32bppRgb:
                    return System.Windows.Media.PixelFormats.Bgr32;
                default:
                    throw new Exception("PixelFormat " + pixelFormat.ToString() + " is not supported.");
            }
        }

        public static BitmapSource Bitmap2Source(Bitmap bitmap)
        {
            var bitmapData = bitmap.LockBits(
                new System.Drawing.Rectangle(0, 0, bitmap.Width, bitmap.Height),
                System.Drawing.Imaging.ImageLockMode.ReadOnly, bitmap.PixelFormat);

            

            var bitmapSource = BitmapSource.Create(
                bitmapData.Width, bitmapData.Height,
                bitmap.HorizontalResolution, bitmap.VerticalResolution,
                ConvertPixelFormat(bitmap.PixelFormat), null,
                bitmapData.Scan0, bitmapData.Stride * bitmapData.Height, bitmapData.Stride);

            bitmap.UnlockBits(bitmapData);
            return bitmapSource;
        }

        public static Bitmap Crop(Bitmap image, Rectangle cropRect)
        {
            Bitmap result = new Bitmap(cropRect.Width, cropRect.Height);

            using (Graphics g = Graphics.FromImage(result))
            {
                g.DrawImage(image, new Rectangle(0, 0, result.Width, result.Height),
                                 cropRect,
                                 GraphicsUnit.Pixel);
            }

            return result;
        }

        #region TextBoxUtils
        public static bool IsUInt(string str)
        {
            return str == String.Empty || str == "+" || uint.TryParse(str, out uint result);
        }
        public static void AllowOnlyUInt(object sender, TextCompositionEventArgs e)
        {
            if (sender is TextBox)
            {
                string text = ((TextBox)sender).Text + e.Text;
                e.Handled = !IsUInt(text);
            }
        }
        public static void AllowOnlyUInt(object sender, DataObjectPastingEventArgs e)
        {
            if (sender is TextBox)
            {
                if (e.DataObject.GetDataPresent(typeof(String)))
                {
                    string text = ((TextBox)sender).Text + (string)e.DataObject.GetData(typeof(String));
                    if (!IsUInt(text))
                    {
                        e.CancelCommand();
                    }
                }
                else
                {
                    e.CancelCommand();
                }
            }
        }

        public static bool Is01Double(string str)
        {
            return str == String.Empty || str == "+" || str == "." || double.TryParse(str, out double result) && result >= 0 && result <= 1;
        }
        public static void AllowOnly01Double(object sender, TextCompositionEventArgs e)
        {
            if (sender is TextBox)
            {
                string text = ((TextBox)sender).Text + e.Text;
                e.Handled = !Is01Double(text);
            }
        }
        public static void AllowOnly01Double(object sender, DataObjectPastingEventArgs e)
        {
            if (sender is TextBox)
            {
                if (e.DataObject.GetDataPresent(typeof(String)))
                {
                    string text = ((TextBox)sender).Text + (string)e.DataObject.GetData(typeof(String));
                    if (!Is01Double(text))
                    {
                        e.CancelCommand();
                    }
                }
                else
                {
                    e.CancelCommand();
                }
            }
        }

        #endregion
    }
}
