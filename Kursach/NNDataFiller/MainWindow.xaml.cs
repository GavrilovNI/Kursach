using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace NNDataFiller
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            comboBox_uiType.ItemsSource = Array.ConvertAll(WindowFiller.LabeledUI.AllowedTypes, x => x.Name).ToList();
            comboBox_uiType.SelectedIndex = 0;

        }

        Bitmap loadedImage;
        private void btn_loadImage_click(object sender, RoutedEventArgs e)
        {
            if(Utils.LoadImage(out loadedImage))
            {
                image.Source = Utils.Bitmap2Source(loadedImage);
            }
        }

        private void btn_MNIST_digits_click(object sender, RoutedEventArgs e)
        {
            Window window = new WindowMNIST_Digits();
            Utils.ChangeWindow(this, window);
        }

        private void btn_start_click(object sender, RoutedEventArgs e)
        {
            if(loadedImage!=null)
            {
                uint.TryParse(textBox_outputsCount.Text, out uint outputsCount);
                uint.TryParse(textBox_sizeX.Text, out uint sizeX);
                uint.TryParse(textBox_sizeY.Text, out uint sizeY);

                if(outputsCount==0 || sizeX==0 || sizeY==0)
                {
                    return;//ERROR
                }

                DataFiller dataFiller = new DataFiller(new System.Drawing.Size((int)sizeX, (int)sizeY), outputsCount);

                WindowFiller windowFiller = new WindowFiller(dataFiller, loadedImage, WindowFiller.LabeledUI.AllowedTypes[comboBox_uiType.SelectedIndex]);

                Utils.ChangeWindow(this, windowFiller, () => {
                    if (dataFiller.Count > 0 && Utils.AskYesNo("Would you like to save data?"))
                        windowFiller.Save();
                });
            }
        }

        
        private void AllowOnlyUInt(object sender, TextCompositionEventArgs e)
        {
            Utils.AllowOnlyUInt(sender, e);
        }
        private void AllowOnlyUInt(object sender, DataObjectPastingEventArgs e)
        {
            Utils.AllowOnlyUInt(sender, e);
        }
    }
}
