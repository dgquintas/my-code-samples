using System;
using System.Data;
using System.Collections.Generic;

namespace CsvDbDiffer
{
    public class DbRecord
    {
        public string Name { get; }

        public string Email { get; }

        public string Department { get; }

        public DbRecord(string name, string email, string department)
        {
            Name = name;
            Email = email;
            Department = department;
        }
    }

    public class DbReader
    {
        private readonly IDbConnection dbcon;

        public DbReader(IDbConnection dbconn)
        {
            this.dbcon = dbconn;
            if (this.dbcon.State != ConnectionState.Open)
            {
                throw new ArgumentException(
                    "Database connection must be in an opened state");
            }
        }

        public IEnumerable<DbRecord> Read()
        {
            const string sql =
                "SELECT name, email, department " +
                "FROM employee ORDER BY name asc";

            IDbCommand dbcmd = dbcon.CreateCommand();
            dbcmd.CommandText = sql;
            IDataReader reader = dbcmd.ExecuteReader();
            while (reader.Read())
            {
                DbRecord db_record = new DbRecord(reader.GetString(0),
                                         reader.GetString(1),
                                         reader.GetString(2));
                yield return db_record;
            }
            reader.Dispose();
            dbcmd.Dispose();
        }


    }
}