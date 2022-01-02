package lab2_2;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class SectionDAO {
    public static Section findById(long id) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM section "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            Section section = null;
            if(rs.next()) {
                section = new Section();
                section.setId(rs.getLong(1));
                section.setName(rs.getString(2));
            }
            st.close();
            return section;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static Section findByName(String name) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM section "
                            + "WHERE name = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, name);
            ResultSet rs = st.executeQuery();
            Section section = null;
            if(rs.next()) {
                section = new Section();
                section.setId(rs.getLong(1));
                section.setName(rs.getString(2));
            }
            st.close();
            return section;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static boolean update(Section section) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "UPDATE section "
                            + "SET name = ? "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, section.getName());
            st.setLong(4, section.getId());
            var result = st.executeUpdate();
            st.close();
            if(result>0)
                return true;
            else
                return false;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean insert(Section section) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "INSERT INTO section (name) "
                            + "VALUES (?) "
                            + "RETURNING id";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, section.getName());
            ResultSet rs = st.executeQuery();
            if(rs.next()) {
                section.setId(rs.getLong(1));
            } else
                return false;
            st.close();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean delete(Section section) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "DELETE FROM section "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, section.getId());
            var result = st.executeUpdate();
            st.close();
            if(result>0)
                return true;
            else
                return false;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static List<Section> findAll(){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM section ";
            PreparedStatement st = connection.prepareStatement(sql);
            ResultSet rs = st.executeQuery();
            List<Section> list = new ArrayList<>();
            while(rs.next()) {
                var section = new Section();
                section.setId(rs.getLong(1));
                section.setName(rs.getString(2));
                list.add(section);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }
}
