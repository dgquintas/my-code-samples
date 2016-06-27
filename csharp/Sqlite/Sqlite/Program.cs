using System;
using System.Data;
using Mono.Data.Sqlite;

public class SQLiteTest
{
  public static void Main()
  {
    const string connectionString = "URI=file::memory:";
    IDbConnection dbcon = new SqliteConnection(connectionString);
    dbcon.Open();
    IDbCommand dbcmd = dbcon.CreateCommand();
    const string sql_create =
      "CREATE TABLE employee (" +
      "name nvarchar(32), " +
      "email nvarchar(64), " +
      "department nvarchar(32));";
    dbcmd.CommandText = sql_create;
    dbcmd.ExecuteNonQuery();

    const string sql_insert = 
      "INSERT INTO employee values ('John Doe', 'lol@foo.com', 'Kittens')";
    dbcmd.CommandText = sql_insert;
    dbcmd.ExecuteNonQuery();

    const string sql =
      "SELECT name, email, department " +
      "FROM employee";
    dbcmd.CommandText = sql;
    IDataReader reader = dbcmd.ExecuteReader();
    while (reader.Read())
      {
        string name = reader.GetString(0);
        string email = reader.GetString(1);
        string department = reader.GetString(2);
        Console.WriteLine("{0} {1} {2}", name, email, department);
      }
    // clean up
    reader.Dispose();
    dbcmd.Dispose();
    dbcon.Close();
  }
}
