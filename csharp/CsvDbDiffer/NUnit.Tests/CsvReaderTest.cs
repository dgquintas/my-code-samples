using NUnit.Framework;
using System;
using System.Data;
using System.Linq;
using System.IO;
using CsvDbDiffer;
using Mono.Data.Sqlite;

namespace NUnit.Tests
{
    [TestFixture]
    public class CsvReaderTest
    {
        public static MemoryStream GetDataStream()
        {
            var stream = new MemoryStream();
            var writer = new StreamWriter(stream);

            writer.WriteLine("Name,Email,Department");
            writer.WriteLine("Rita Marley,weed@420.com,Potheads");
            writer.WriteLine("John Doe,foo@bar.com,Lolailo");
            writer.Flush();
            stream.Position = 0;

            return stream;
        }

        [Test]
        public void TestRead()
        {
            CsvRecord[] expected_records =
                {
                    new CsvRecord
                    {
                        Name = "John Doe",
                        Email = "foo@bar.com",
                        Department = "Lolailo"
                    },
                    new CsvRecord
                    {
                        Name = "Rita Marley",
                        Email = "weed@420.com",
                        Department = "Potheads"
                    }
                };
            var reader = new CsvReader(
                             new StreamReader(GetDataStream()));
            var records = reader.Read();
            var pairs = records.Zip(expected_records, Tuple.Create);
            foreach (var p in pairs)
            {
                Assert.AreEqual(p.Item1, p.Item2);
            }
        }
    }

    [TestFixture]
    public class DbReaderTest
    {
        SqliteConnection conn;

        [TestFixtureSetUp]
        public void SetupDb()
        {
            conn = new SqliteConnection("URI=file::memory:");
            conn.Open();
            IDbCommand dbcmd = conn.CreateCommand();
            const string sql_create =
                "CREATE TABLE employee (" +
                "name nvarchar(32), " +
                "email nvarchar(64), " +
                "department nvarchar(32));";
            dbcmd.CommandText = sql_create;
            dbcmd.ExecuteNonQuery();

            string sql_insert = 
                "INSERT INTO employee values ('John Doe', 'lol@foo.com', 'Kittens')";
            dbcmd.CommandText = sql_insert;
            dbcmd.ExecuteNonQuery();

            sql_insert = 
                "INSERT INTO employee values ('Rita Marley', 'lol@foo.com', 'Kittens')";
            dbcmd.CommandText = sql_insert;
            dbcmd.ExecuteNonQuery();
            dbcmd.Dispose();
        }

        [Test]
        public void TestRead()
        {
            DbReader reader = new DbReader(conn);
            var records = reader.Read();
            var r = records.ElementAt(0);
            Assert.AreEqual(r.Name, "John Doe");
            Assert.AreEqual(r.Email, "lol@foo.com");
            Assert.AreEqual(r.Department, "Kittens");
            r = records.ElementAt(1);
            Assert.AreEqual(r.Name, "Rita Marley");
            Assert.AreEqual(r.Email, "lol@foo.com");
            Assert.AreEqual(r.Department, "Kittens");
        }
    }
}

