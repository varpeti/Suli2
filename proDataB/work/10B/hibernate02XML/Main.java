package hibernate02XML;

import java.util.Date;

import org.hibernate.Session;
import hibernate02XML.HibernateUtil;


public class Main {
	public static void main(String[] args) {
		System.out.println(" Hibernate + XML mapping");
		

		Session session = HibernateUtil.getSessionFactory().openSession();

		session.beginTransaction();
		DBUser user = new DBUser();

		user.setUserId(100);
		user.setUsername("superman");
		user.setCreatedBy("system");
		user.setCreatedDate(new Date());

		session.save(user);
		session.getTransaction().commit();
		
		System.out.println("Done");
		HibernateUtil.shutdown();

	

	}
}
