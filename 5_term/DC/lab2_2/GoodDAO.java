package lab2_2;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class GoodDAO {
    public static Good findById(long id) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM good "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            Good good = null;
            if(rs.next()) {
                good = new Good();
                good.setId(rs.getLong(1));
                good.setName(rs.getString(2));
                good.setSectionId(rs.getLong(3));
                good.setPrice(rs.getLong(4));
            }
            st.close();
            return good;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static Good findByName(String name) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM good "
                            + "WHERE name = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, name);
            ResultSet rs = st.executeQuery();
            Good good = null;
            if(rs.next()) {
                good = new Good();
                good.setId(rs.getLong(1));
                good.setName(rs.getString(2));
                good.setSectionId(rs.getLong(3));
                good.setPrice(rs.getLong(4));
            }
            st.close();
            return good;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static boolean update(Good good) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "UPDATE good "
                            + "SET name = ?, sectionid = ?, price = ? "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, good.getName());
            st.setLong(2, good.getSectionId());
            st.setLong(3, good.getPrice());
            st.setLong(4, good.getId());
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

    public static boolean insert(Good good) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "INSERT INTO good (name,sectionid,price) "
                            + "VALUES (?,?,?) "
                            + "RETURNING id";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setString(1, good.getName());
            st.setLong(2, good.getSectionId());
            st.setLong(3, good.getPrice());
            ResultSet rs = st.executeQuery();
            if(rs.next()) {
                good.setId(rs.getLong(1));
            } else
                return false;
            st.close();
            return true;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return false;
    }

    public static boolean delete(Good good) {
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "DELETE FROM good "
                            + "WHERE id = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, good.getId());
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

    public static List<Good> findAll(){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM good";
            PreparedStatement st = connection.prepareStatement(sql);
            ResultSet rs = st.executeQuery();
            List<Good> list = new ArrayList<>();
            while(rs.next()) {
                var good = new Good();
                good.setId(rs.getLong(1));
                good.setName(rs.getString(2));
                good.setSectionId(rs.getLong(3));
                good.setPrice(rs.getLong(4));
                list.add(good);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }

    public static List<Good> findBySectionId(Long id){
        try(Connection connection = DBConnection.getConnection();) {
            String sql =
                    "SELECT * "
                            + "FROM good "
                            + "WHERE sectionid = ?";
            PreparedStatement st = connection.prepareStatement(sql);
            st.setLong(1, id);
            ResultSet rs = st.executeQuery();
            List<Good> list = new ArrayList<>();
            while(rs.next()) {
                var good = new Good();
                good.setId(rs.getLong(1));
                good.setName(rs.getString(2));
                good.setSectionId(rs.getLong(3));
                good.setPrice(rs.getLong(4));
                list.add(good);
            }
            st.close();
            return list;
        } catch (SQLException e1) {
            e1.printStackTrace();
        }
        return null;
    }
}
