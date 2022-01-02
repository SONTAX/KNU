package lab3_2.server;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Good {
    private Long id;
    private Long sectionId;
    private String name;
    private Long price;
}
