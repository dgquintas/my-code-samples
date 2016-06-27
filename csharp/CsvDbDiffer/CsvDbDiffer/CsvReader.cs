using System;
using System.Linq;
using System.IO;
using System.Collections.Generic;

namespace CsvDbDiffer
{

    public class CsvRecord : IEquatable<CsvRecord>
    {
        public string Name { get; set; }

        public string Email { get; set; }

        public string Department { get; set; }

        public bool Equals(CsvRecord other)
        {
            if (other == null)
            {
                return false;
            }
            if (this.Name == other.Name &&
                this.Email == other.Email &&
                this.Department == other.Department)
            {
                return true;
            }
            return false;
        }

        public override string ToString()
        {
            return string.Format("CsvRecord[{0}, {1}, {2}]", 
                Name, Email, Department);
        }
            
    }

    public class CsvReader
    {
        private readonly StreamReader stream;

        public CsvReader(StreamReader stream)
        {
            this.stream = stream;
        }

        public IEnumerable<CsvRecord> Read()
        {
            using (var reader =
                       new CsvHelper.CsvReader(this.stream))
            {
                var sorted_records = 
                    from record in reader.GetRecords<CsvRecord>()
                                   orderby record.Name ascending
                                   select record;

                foreach (CsvRecord r in sorted_records)
                {
                    yield return r;
                }
            }
        }
    }
}