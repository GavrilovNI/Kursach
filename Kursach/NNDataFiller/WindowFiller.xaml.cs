using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace NNDataFiller
{
    /// <summary>
    /// Логика взаимодействия для WindowFiller.xaml
    /// </summary>
    public partial class WindowFiller : Window
    {
        private DataFiller _dataFiller;

        private LabeledUI[] _outputs;

        private System.Drawing.Point _currPos;

        private Random _random;

        public class LabeledUI
        {
            public Label label;
            public FrameworkElement ui;

            public static Type[] AllowedTypes => new Type[] { typeof(TextBox), typeof(CheckBox), typeof(RadioButton) };

            public LabeledUI(Type uiType)
            {
                if(!Array.Exists(AllowedTypes, x=>x==uiType))
                {
                    throw new Exception("wrong uiType");
                }

                label = new Label();
                ui = (FrameworkElement)Activator.CreateInstance(uiType);
            }

        }

        public WindowFiller(DataFiller filler, Type uiType, string[] outputNames) : this(filler, uiType)
        {
            if (outputNames.Length != _outputs.Length)
            {
                throw new Exception("wrong length of outputsNames");
            }

            for (int i = 0; i < _outputs.Length; i++)
            {
                _outputs[i].label.Content = outputNames[i];
            }
        }

        public WindowFiller(DataFiller filler, Type uiType)
        {
            this._dataFiller = filler;
            InitializeComponent();

            
            RenderOptions.SetBitmapScalingMode(this.image, BitmapScalingMode.HighQuality);

            const double border = 5;
            const double outputHeight = 30;

            while (grid.RowDefinitions.Count < filler.OutputsCount)
            {
                grid.RowDefinitions.Add(new RowDefinition());
            }
            for (int i = 0; i < grid.RowDefinitions.Count - 1; i++)
            {
                grid.RowDefinitions[i].Height = new GridLength(outputHeight + border * 2);
            }

            Grid.SetRowSpan(this.image, (int)filler.OutputsCount);

            //grid.ColumnDefinitions.Add(new ColumnDefinition());

            _outputs = new LabeledUI[filler.OutputsCount];

            for (int i = 0; i < _outputs.Length; i++)
            {
                _outputs[i] = new LabeledUI(uiType);

                _outputs[i].label.Content = "output " + i + ":";
                _outputs[i].label.VerticalAlignment = VerticalAlignment.Top;
                _outputs[i].label.HorizontalAlignment = HorizontalAlignment.Left;
                _outputs[i].label.Margin = new Thickness(border, border, 0, 0);
                _outputs[i].label.Height = outputHeight;
                _outputs[i].label.Width = 70;

                /*if(uiType==typeof(TextBox))
                {
                    TextBox textBox = (TextBox)_outputs[i].ui;
                }
                else */if(uiType == typeof(RadioButton))
                {
                    RadioButton radioBtn = (RadioButton)_outputs[i].ui;
                    radioBtn.GroupName = "Output";
                    if (i == 0)
                    {
                        radioBtn.IsChecked = true;
                    }
                }
                /*else if(uiType==typeof(CheckBox))
                {
                    CheckBox checkBox = (CheckBox)_outputs[i].ui;
                }*/
                _outputs[i].ui.VerticalAlignment = VerticalAlignment.Top;
                _outputs[i].ui.HorizontalAlignment = HorizontalAlignment.Left;
                _outputs[i].ui.Margin = new Thickness(_outputs[i].label.Width + border * 2, border, 0, 0);
                _outputs[i].ui.Height = outputHeight;
                _outputs[i].ui.Width = 100;


                _outputs[i].ui.PreviewTextInput += Utils.AllowOnly01Double;
                DataObject.AddPastingHandler(_outputs[i].ui, Utils.AllowOnly01Double);

                Grid.SetColumn(_outputs[i].label, grid.ColumnDefinitions.Count - 1);
                Grid.SetColumn(_outputs[i].ui, grid.ColumnDefinitions.Count - 1);
                Grid.SetRow(_outputs[i].label, i);
                Grid.SetRow(_outputs[i].ui, i);
                grid.Children.Add(_outputs[i].label);
                grid.Children.Add(_outputs[i].ui);
            }

            var lastOutput = _outputs[_outputs.Length - 1];

            
            btn_next.Margin = new Thickness(lastOutput.ui.Margin.Left + lastOutput.ui.Width + border, border, 0, 0);
            btn_next.Height = outputHeight;
            Grid.SetColumn(btn_next, grid.ColumnDefinitions.Count - 1);
            Grid.SetRow(btn_next, _outputs.Length - 1);

            btn_save.Margin = new Thickness(btn_next.Margin.Left + btn_next.Width + border, border, 0, 0);
            btn_save.Height = outputHeight;
            Grid.SetColumn(btn_save, grid.ColumnDefinitions.Count - 1);
            Grid.SetRow(btn_save, _outputs.Length - 1);
            UpdateBtnSaveEnabled();

            _random = new Random();

            Next();
        }

        private double[] GetOutputs()
        {
            double[] result = new double[_outputs.Length];
            
            for (int i = 0; i < result.Length; i++)
            {
                if(_outputs[i].ui is TextBox)
                {
                    TextBox textBox = (TextBox)_outputs[i].ui;
                    double.TryParse(textBox.Text, out result[i]);
                }
                else if(_outputs[i].ui is ToggleButton)
                {
                    ToggleButton toggleBtn = (ToggleButton)_outputs[i].ui;
                    result[i] = toggleBtn.IsChecked == true ? 1 : 0;
                }
            }
            return result;
        }

        public void Add()
        {
            _dataFiller.Add(_currPos, GetOutputs());
        }
        public void Next()
        {
            _currPos = new System.Drawing.Point(_random.Next(_dataFiller.Image.Width - _dataFiller.DataSize.Width),
                                        _random.Next(_dataFiller.Image.Height - _dataFiller.DataSize.Height));

            this.image.Source = Utils.Bitmap2Source(Utils.Crop(_dataFiller.Image, new System.Drawing.Rectangle(_currPos, _dataFiller.DataSize)));
        }

        private void UpdateBtnSaveEnabled()
        {
            btn_save.IsEnabled = _dataFiller.Count > 0;
        }

        private void btn_next_click(object sender, RoutedEventArgs e)
        {
            Add();
            Next();
            UpdateBtnSaveEnabled();
        }

        public void Save()
        {
            if (Utils.GetPath(out string path, "Data files|*.data"))
            {
                using (BinaryWriter writer = new BinaryWriter(File.Open(path, FileMode.OpenOrCreate)))
                {
                    writer.BaseStream.Position = writer.BaseStream.Length;
                    _dataFiller.SaveAndClear(writer);
                    UpdateBtnSaveEnabled();
                }
            }
        }

        private void btn_save_click(object sender, RoutedEventArgs e)
        {
            Save();
        }
    }
}
