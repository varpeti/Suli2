
import java.sql.*;
import oracle.jdbc.pool.*;

public class Main
{
    public static void main(String[] args) 
    {
        Connection con = null;
        Statement stmt = null;
        try
        {
            System.out.println("HW");
            String jdbcURL = "jdbc:oracle:thin:@//dboracle.itk.ppke.hu:1521/lab.itk.ppke.hu";
            String user = "AD18_VARPET";
            String pass = "idejonajelszo";
            OracleDataSource ods = new OracleDataSource();
            ods.setURL(jdbcURL);
            ods.setUser(user);
            ods.setPassword(pass);
            
            con = ods.getConnection();
            System.out.println("getConnection");

            stmt = con.createStatement();
            System.out.println("createStatement");

            String sql = "SELECT * FROM student";
            ResultSet rs = stmt.executeQuery(sql);
            while(rs.next())
            {
    
                //Display values
                System.out.print("Name: " + rs.getString("name"));
                System.out.print(", Sex: " + rs.getString("sex"));
                System.out.println(", ID: " + rs.getInt("student_id"));
            }
            rs.close();
        }
        catch (SQLException e) 
        {
            // Could not connect to the database
            System.out.println("Can't connect to database");
        }
        catch(Exception e)
        {
        }
        finally
        {
            try
            {
                if(con!=null) con.close();
            }
            catch(Exception e)
            {
            }
        }
        
        try{System.out.println("Press ENTER to Exit!");System.in.read();}catch(Exception e){} //TODO remove
    }
}