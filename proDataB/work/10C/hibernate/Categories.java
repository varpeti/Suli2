package hibernate;

import javax.persistence.*;

@Entity(name="Categories")
public class Categories {
	@Id @GeneratedValue 
	private int category_id;
	
	@Column(name="name")
	private String name;

	@Column(name="longname")
	private String description;
	
	public int getCategory_id() {
		return category_id;
	}

	public void setCategory_id(int category_id) {
		this.category_id = category_id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

}
