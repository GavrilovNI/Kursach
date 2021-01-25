using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.IO;

namespace NNDataFiller
{
    
    public class DataFiller
    {
        public Bitmap Image { get; private set; }

        public Size DataSize { get; private set; }
        public uint OutputsCount { get; private set; }

        public int Count => _data.Count;

        private Dictionary<Point, double[]> _data = new Dictionary<Point, double[]>();



        public DataFiller(Size dataSize, uint outputsCount)
        {
            this.DataSize = dataSize;
            this.OutputsCount = outputsCount;
        }

        public void Add(Point position, double[] outputs)
        {
            if (outputs.Length != OutputsCount)
                throw new Exception("wrong outnputs length");
            _data[position] = outputs;
        }



        public void SaveAndClear(BinaryWriter writer)
        {
            writer.Write(DataSize.Width);
            writer.Write(DataSize.Height);
            writer.Write(OutputsCount);

            writer.Write(_data.Count);
            foreach (var entry in _data)
            {
                writer.Write(entry.Key.X);
                writer.Write(entry.Key.Y);
                for (int i = 0; i < entry.Value.Length; i++)
                {
                    writer.Write(entry.Value[i]);
                }
            }

            _data.Clear();
        }

        


    }
}
