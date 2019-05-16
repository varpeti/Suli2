package hibernate;

import org.hibernate.Session;

public class Main {

	public static void main(String[] args) {
		System.out.println(" Hibernate + XML mapping");
		
		Session session = HibernateUtil.getSessionFactory().openSession();

		session.beginTransaction();
		Categories categ = new Categories();

		categ.setCategory_id(100);
		categ.setDescription("hosszunev");
		categ.setName("nev");

		session.save(categ);
		session.getTransaction().commit();
		
		System.out.println("Done");
		HibernateUtil.shutdown();

		try{System.in.read();}catch(Exception e){} //TODO: earse me
	}

}
