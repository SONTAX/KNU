package lab1_2;

import java.util.ArrayList;
import java.util.List;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class Section {
    private String id;
    private String name;
    private List<Good> cities = new ArrayList<>();
}
