package lab1_2;

import java.util.HashMap;
import java.util.Map;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class Warehouse {
    private Map<String, Section> sections = new HashMap<>();
    private Map<String, String> sectionNames = new HashMap<>();
    private Map<String, Good> goods = new HashMap<>();
    private Map<String, String> goodNames = new HashMap<>();

    public void generateId(Section section) {
        var id = sections.size();
        String idStr = "x"+id;
        while(sections.get(idStr) != null) {
            id++;
            idStr = "x"+id;
        }
        section.setId(idStr);
    }
    public void generateId(Good good) {
        var id = goods.size();
        String idStr = "id"+id;
        while(goods.get(idStr) != null) {
            id++;
            idStr = "id"+id;
        }
        good.setId(idStr);
    }

    public void addSection(Section section) {
        var changed = false;
        if(sections.get(section.getId())!=null) {
            changed = true;
            generateId(section);
        }
        if (changed) {
            for(Good ct: section.getCities())
                ct.setSectionId(section.getId());
        }
        sections.put(section.getId(), section);
        sectionNames.put(section.getName(), section.getId());
    }

    public void removeSection(Section section) {
        sections.remove(section.getId());
        sectionNames.remove(section.getName());
        for(Good ct: section.getCities())
            goods.remove(ct.getId());
    }

    public void addGood(Good good) {
        if(goods.get(good.getId())!=null) {
            generateId(good);
        }
        goods.put(good.getId(),good);
        sections.get(good.getSectionId()).getCities().add(good);
        goodNames.put(good.getName(), good.getId());
    }

    public void removeGood(Good good) {
        goods.remove(good.getId());
        goodNames.remove(good.getName());
        sections.get(good.getSectionId()).getCities().remove(good);
    }

    public void transferGood(Good good, Section section) {
        var old = sections.get(good.getSectionId());
        if (old != null)
            old.getCities().remove(good);
        good.setSectionId(section.getId());
        section.getCities().add(good);
    }

    public void rename(Section section, String name) {
        sectionNames.remove(section.getName());
        section.setName(name);
        sectionNames.put(section.getName(),section.getId());
    }
    public void rename(Good good, String name) {
        goodNames.remove(good.getName());
        good.setName(name);
        goodNames.put(good.getName(),good.getId());
    }


    public Section getSection(String name) {
        var id = sectionNames.get(name);
        if(id != null)
            return sections.get(id);
        return null;
    }
    public Good getGood(String name) {
        var id = goodNames.get(name);
        if(id != null)
            return goods.get(id);
        return null;
    }
}
