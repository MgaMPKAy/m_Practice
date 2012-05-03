Section simple_proofs.

Variables P Q R S : Prop.

Lemma id_P : P -> P.
Proof.
  intros H.
  assumption.
Qed.

Lemma id_PP : (P->P)->(P->P).
Proof.
  intros H.
  assumption.
Qed.

Lemma imp_trans : (P->Q)->(Q->R)->P->R.
Proof.
  intros H H0 p.
  apply H0.
  apply H.
  assumption.
Qed.

Lemma imp_perm : (P->Q->R)->(Q->P->R).
Proof.
  intros H q p.
  apply H.
  assumption.
  assumption.
Qed.

Lemma ignore_Q : (P->R)->P->Q->R.
Proof.
  intros H p q.
  apply H.
  assumption.
Qed.

Lemma delta_imp  : (P->P->Q)->P->Q.
Proof.
  intros H p.
  apply H.
  assumption.
  assumption.
Qed.

Lemma delta_impR : (P->Q)->(P->P->Q).
Proof.
  intros H p p1.
  apply H.
  assumption.
Qed.

Lemma diamond : (P->Q)->(P->R)->(Q->R->S)->P->S.
Proof.
  intros H H1 H2 p.
  apply H2.
  apply H.
  assumption.
  apply H1.
  assumption.
Qed.


Lemma weak_peirce : ((((P->Q)->P)->P)->Q)->Q.
Proof.
  intros H.
  apply H.
  intros H0.
  apply H0.
  intros p.
  apply H.
  intros H1.
  assumption.
Qed.
